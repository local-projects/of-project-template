#extension GL_EXT_gpu_shader4 : require


varying vec2 vTexCoord; //used to forward vertex texCoords to fragment shader

void main(void){

	vTexCoord = gl_MultiTexCoord0.xy; //get tex coords form mesh - forward to fragment shader
	gl_FrontColor = gl_Color;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
