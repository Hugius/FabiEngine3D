#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

in vec2 f_uv;

// Texture uniforms
uniform sampler2D u_sampler_diffuse;

// Float uniforms
uniform float u_bloomBrightnessTreshold;

layout (location = 0) out vec4 o_finalColor;

void main()
{
	// Diffuse mapping
    vec4 diffuseColor = texture(u_sampler_diffuse, f_uv);

	// Tonemapping (HDR to LDR)
	//vec3 tonemappedColor = diffuseColor.rgb / (diffuseColor.rgb + vec3(1.0f)); // Reinhard tone mapping
	vec3 tonemappedColor = vec3(1.0f) - exp(-diffuseColor.rgb * 1.0f);        // Exposure tone mapping
	diffuseColor = vec4(tonemappedColor, 1.0f);

    // Bright color extraction for bloom
	float brightness = dot(diffuseColor.rgb, vec3(0.2126f, 0.7152f, 0.0722f));
	if(brightness > u_bloomBrightnessTreshold) 
	{
		o_finalColor = diffuseColor;
	}
	else
	{
		o_finalColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
}