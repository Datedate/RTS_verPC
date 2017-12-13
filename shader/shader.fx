float4x4 g_MatWorld;					// ワールド変換行列
float4x4 g_MatProjection;				// 射影変換行列
texture  g_Texture;						// テクスチャ

// テクスチャから色を取得する変数
sampler texSampler = sampler_state {		
	texture = <g_Texture>;					// g_Texture変数から色を取得する
};

struct VS_Input {
	float3 localpos : POSITION;
	float2 uv		: TEXCOORD0;
};

struct VS_Output {
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

float uv_left;
float uv_top;
float uv_width;
float uv_height;
float alpha;

float pivot_x;
float pivot_y;

// 指定UVのディフューズカラーを取得する
float4 getDiffuseColor(float2 uv) {
	float4 color = tex2D(texSampler, uv);
	color.a *= alpha;
	return color;
	//return tex2D(texSampler, uv);			// テクスチャ有り
//	return float4(1.0f, 0.0f, 0.0f, 0.15f);	// テクスチャ無し
}


// 頂点シェーダ
VS_Output vs_main(VS_Input vs_in ) {
	VS_Output vs_out = (VS_Output)0;

	// 座標変換
	// pivot分ずらす
	vs_out.pos = float4(vs_in.localpos,1.0f) - float4(pivot_x, pivot_y, 0.0f, 0.0f);
	vs_out.pos = mul(vs_out.pos, g_MatWorld);
	// 元の位置に戻す
	vs_out.pos += float4(pivot_x, pivot_y, 0.0f, 0.0f);
	vs_out.pos = mul(vs_out.pos, g_MatProjection);

	vs_out.uv = vs_in.uv * float2(uv_width, uv_height) + float2(uv_left, uv_top);

	return vs_out;
}

// ピクセルシェーダー
float4 ps_main(VS_Output ps_in) :COLOR0{
	return getDiffuseColor(ps_in.uv);
}

// テクニック
technique Tech {
	pass p0 {
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();

		// アルファブレンドモード
		AlphaBlendEnable = true;
		SrcBlend		 = SRCALPHA;
		DestBlend		 = INVSRCALPHA;
	}
}