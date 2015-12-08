#version 150
// A texture is expected as program attribute
uniform sampler2D Texture;
uniform vec3 ViewPosition;

// The vertex shader fill feed this input
in vec2 FragTexCoord;

// Wordspace normal
in vec4 normal;

// Position
in vec3 position;

// The final color
out vec4 FragmentColor;

// Light direction in world coordinates
vec4 lightDirection = normalize(vec4(2.0f,1.0f,-7.0f,0.0f));
vec4 lightColor = normalize(vec4(0.3f,0.3f,0.3f,0.0f));

void main() {
  // Ambient lighting
  float ambientStrength = 0.6f;
  vec4 ambient = ambientStrength * lightColor;

  // Compute diffuse lighting
  float diff = max(dot(normal, lightDirection), 0.0f);
  vec4 diffuse = diff * lightColor;

  // Specular lighting
  float specularStrength = 1.0f;
  vec4 viewDir = vec4(normalize(ViewPosition - position), 1.0f);
  vec4 reflectDir = reflect(-lightDirection, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec4 specular = specularStrength * spec * lightColor;


  // Lookup the color in Texture on coordinates given by fragTexCoord and apply diffuse lighting
  FragmentColor = texture(Texture, FragTexCoord) * (ambient + diffuse + specular);
}
