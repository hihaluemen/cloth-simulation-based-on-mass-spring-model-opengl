uniform sampler2D positions;//[1]
uniform sampler2D prevPositions;//[2]
uniform float timeStep;//[5]
uniform float fixedPoints[100];//[0]
uniform float DAMPING;//[3]
uniform float MASS;//[4]
uniform float KsStruct;//[5]
uniform float KdStruct;//[6]
uniform float KsShear;//[7]
uniform float KdShear;//[8]
uniform float KsBend;//[9]
uniform float KdBend;//[10]
uniform float windX;
uniform float windY;
uniform float windZ;
uniform vec3 GRAVITY;//[11]
uniform float clothTextureWidth;//[12]
uniform float clothTextureHeight;//[13]
uniform vec2 realDistanceOfXandY;//[14]
uniform vec2 textureDistanceOfXandY;//[15]

vec2 neighbor(int index, out float ks, out float kd){
    if(index < 4){
        ks = KsStruct;
        kd = KdStruct;
        if(index == 0) return vec2(1, 0);
        if(index == 1) return vec2(0, -1);
        if(index == 2) return vec2(-1, 0);
        if(index == 3) return vec2(0, 1);
    }
    if(4 <= index && index < 8){
        ks = KsShear;
        kd = KdShear;
        if(index == 4) return vec2(1, -1);
        if(index == 5) return vec2(-1, -1);
        if(index == 6) return vec2(-1, 1);
        if(index == 7) return vec2(1, 1);
    }
    if(8 <= index && index < 12){
        ks = KsBend;
        kd = KdBend;
        if(index == 8) return vec2(2, 0);
        if(index == 9) return vec2(0, -2);
        if(index == 10) return vec2(-2, 0);
        if(index == 11) return vec2(0, 2);
    }
}

void main(){
    float currentParticleMass = MASS;
    float ks = 0.0;
    float kd = 0.0;
    float indexOfX = floor(gl_TexCoord[0].s * clothTextureWidth);
    float indexOfY = floor(gl_TexCoord[0].t * clothTextureHeight);
    float index = indexOfX + indexOfY * clothTextureWidth;
    vec3 currentParticlePosition = texture2D(positions, gl_TexCoord[0].st).xyz;
    vec3 currentParticlePrevPosition = texture2D(prevPositions, gl_TexCoord[0].st).xyz;
    vec3 currentParticleVelocity = (currentParticlePosition - currentParticlePrevPosition) / timeStep;
    for(int i = 0; i < 100; i++){
        if(index == fixedPoints[i]){
            currentParticleMass = 0.0;
            break;
        }
    }
    vec3 force = GRAVITY * currentParticleMass + currentParticleVelocity * DAMPING;
    force.x += windX;
	force.y += windY;
	force.z += windZ;
	vec3 acceleration;
    for(int kind = 0; kind < 12; kind++){
        vec2 neighborRelativeCoordinates = neighbor(kind, ks, kd);
        float j = neighborRelativeCoordinates.x;
		float i = neighborRelativeCoordinates.y;
		if (((indexOfY + i) < 0.0) || ((indexOfY + i) > (clothTextureHeight - 1.0)))
			continue;
		if (((indexOfX + j) < 0.0) || ((indexOfX + j) > (clothTextureWidth - 1.0)))
			continue;	
        vec2 neighborTextureCoordinates = vec2(indexOfX + j, indexOfY + i) * textureDistanceOfXandY;
        float naturalLength = length(neighborRelativeCoordinates * realDistanceOfXandY);
        vec3 neighborPosition = texture2D(positions, neighborTextureCoordinates).xyz;
        vec3 neighborVelocity = (neighborPosition - texture2D(prevPositions, neighborTextureCoordinates).xyz) / timeStep;
        vec3 deltaPosition = currentParticlePosition - neighborPosition;
        vec3 deltaVelocity = currentParticleVelocity - neighborVelocity;
        float distance = length(deltaPosition);
        force += (-ks * (distance - naturalLength) + kd * (dot(deltaVelocity, deltaPosition) / distance)) * normalize(deltaPosition);
    }
    if(currentParticleMass == 0){
        acceleration = vec3(0.0);
    }else{
        acceleration = force / currentParticleMass;
    }
    vec3 temp = currentParticlePosition;
    currentParticlePosition = currentParticlePosition * 2.0 - currentParticlePrevPosition + acceleration * timeStep * timeStep;
    currentParticlePrevPosition = temp;
    gl_FragData[0] = vec4(currentParticlePosition, 1.0);
    gl_FragData[1] = vec4(currentParticlePrevPosition, 0.0);
}