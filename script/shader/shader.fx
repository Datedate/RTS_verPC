float4x4 projection;

struct VS_Input {
	float3 pos : POSITION;
};

struct VS_Output {
	float4 pos : POSITION;
};

// 頂点シェーダ
VS_Output vs_main(VS_Input vs_in) {
	VS_Output vs_out = (VS_Output)0;

	vs_output = mul(float4(vs_in.pos, 1.0f), projection);

	return vs_out;
}

// ピクセルシェーダー
float4 ps_main(VS_Output ps_in) :COLOR0{
	return float4 (1.0f,0.0f,0.0f,1.0f);
}

technique Tech {
	pass p0 {
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
}