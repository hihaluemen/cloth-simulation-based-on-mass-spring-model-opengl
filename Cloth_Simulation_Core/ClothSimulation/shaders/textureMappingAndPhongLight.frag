uniform sampler2D map;
uniform sampler2D tex;//[2]
uniform vec3 lightColor;//[4]
uniform vec3 cameraPosition;//[2]
//uniform vec3 lightPosition;

varying vec2 origin;
varying vec2 textureCoordinate;
varying vec3 particleNormalVector;
varying vec4 realCoordinate;

void main(){
    vec3 pos = realCoordinate.xyz;
    vec3 normal = particleNormalVector;
    vec3 viewDirection = normalize(cameraPosition - pos);
    //vec3 lightDirection = normalize(lightPosition - pos);
    vec3 lightDirection = vec3(1.0, 1.0, 1.0);
    lightDirection = normalize(lightDirection);
    if(dot(viewDirection, normal) <= 0.0){
        normal = -normal;
    }
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float lamb = max(dot(lightDirection, normal), 0.0);
    float spec = 0.0;
    float amb = 0.2;
    if(lamb > 0.0){
        float specAngle = max(dot(reflectDirection, viewDirection), 0.0);
        spec = pow(specAngle, 1.0);
    }
    vec4 textureColor = texture2D(tex, vec2(1.0 - textureCoordinate.x, 1.0 - textureCoordinate.y));
    gl_FragColor = vec4(((lamb + spec + amb) * lightColor), 1.0) + textureColor;
}