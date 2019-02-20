uniform sampler2D map;
uniform float widthInterval;//[0]
uniform float heightInterval;//[1]

varying vec2 origin;
varying vec2 textureCoordinate;
varying vec3 particleNormalVector;
varying vec4 realCoordinate;

vec3 calculateNormalVector(vec3 particleX, vec3 particleY, vec3 particleZ){
    vec3 normalVector;
    vec3 e1 = particleY - particleX;
    vec3 e2 = particleZ - particleX;
    normalVector.x = e1.y * e2.z - e1.z * e2.y;
    normalVector.y = e1.z * e2.x - e1.x * e2.z;
    normalVector.z = e1.x * e2.y - e1.y * e2.x;
    normalVector = normalize(normalVector);
    return normalVector;
}

void main(){
    origin = gl_Vertex.xy;
    textureCoordinate = gl_Vertex.xy + vec2(1.0 / widthInterval, 1.0 / heightInterval);
    realCoordinate = vec4(texture2D(map, textureCoordinate).rgb, 1.0);
    vec3 up = texture2D(map, textureCoordinate + vec2(0.0, 1.0 / heightInterval)).rgb;
    vec3 down = texture2D(map, textureCoordinate + vec2(0.0, -1.0 / heightInterval)).rgb;
    vec3 left = texture2D(map, textureCoordinate + vec2(-1.0 / widthInterval, 0.0)).rgb;
    vec3 right = texture2D(map, textureCoordinate + vec2(1.0 / widthInterval, 0.0)).rgb;
    particleNormalVector = vec3(0.0, 0.0, 0.0);
    vec3 normalUpRight = calculateNormalVector(realCoordinate.xyz, up, right);
    vec3 normalDownRight = calculateNormalVector(realCoordinate.xyz, right, down);
    vec3 normalDownLeft = calculateNormalVector(realCoordinate.xyz, down, left);
    vec3 normalUpLeft = calculateNormalVector(realCoordinate.xyz, right, up);
    if(dot(normalUpRight, normalDownRight) <= 0.0){
        normalDownRight = -normalDownRight;
    }
    if(dot(normalUpRight, normalDownLeft) <= 0.0){
        normalDownLeft = -normalDownLeft;
    }
    if(dot(normalUpRight, normalUpLeft) <= 0.0){
        normalUpLeft = -normalUpLeft;
    }
    particleNormalVector += (normalUpRight + normalDownRight + normalDownLeft + normalUpLeft);
    if(textureCoordinate.x <= 0.5 / widthInterval || textureCoordinate.y <= 0.5 / heightInterval || textureCoordinate.x >= 1.0 - 0.5 / widthInterval || textureCoordinate.y >= 1.0 - 0.5 / widthInterval){
        particleNormalVector = vec3(0.0, 0.0, 0.0);
    }
	particleNormalVector = normalize(particleNormalVector);
    gl_Position = gl_ModelViewProjectionMatrix * realCoordinate;
}