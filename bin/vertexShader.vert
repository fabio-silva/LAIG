uniform sampler2D blue;

void main()
{
	vec4 offset = vec4(0.0, 0.0, 0.0, 0.0);
	
	if( texture2D(blue, vec2(1.0, 1.0) - gl_MultiTexCoord0.st).b > 0.5)
		offset.xyz = gl_Normal*0.1*0.1;
		
	gl_Position = gl_ModelViewProjectionMatrix * (gl_Vertex + offset);
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
}