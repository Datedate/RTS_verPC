float4x4 g_MatWorld;					// ���[���h�ϊ��s��
float4x4 g_MatProjection;				// �ˉe�ϊ��s��
texture  g_Texture;						// �e�N�X�`��

// �e�N�X�`������F���擾����ϐ�
sampler texSampler = sampler_state {		
	texture = <g_Texture>;					// g_Texture�ϐ�����F���擾����
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

// �w��UV�̃f�B�t���[�Y�J���[���擾����
float4 getDiffuseColor(float2 uv) {
	float4 color = tex2D(texSampler, uv);
	color.a *= alpha;
	return color;
	//return tex2D(texSampler, uv);			// �e�N�X�`���L��
//	return float4(1.0f, 0.0f, 0.0f, 0.15f);	// �e�N�X�`������
}


// ���_�V�F�[�_
VS_Output vs_main(VS_Input vs_in ) {
	VS_Output vs_out = (VS_Output)0;

	// ���W�ϊ�
	// pivot�����炷
	vs_out.pos = float4(vs_in.localpos,1.0f) - float4(pivot_x, pivot_y, 0.0f, 0.0f);
	vs_out.pos = mul(vs_out.pos, g_MatWorld);
	// ���̈ʒu�ɖ߂�
	vs_out.pos += float4(pivot_x, pivot_y, 0.0f, 0.0f);
	vs_out.pos = mul(vs_out.pos, g_MatProjection);

	vs_out.uv = vs_in.uv * float2(uv_width, uv_height) + float2(uv_left, uv_top);

	return vs_out;
}

// �s�N�Z���V�F�[�_�[
float4 ps_main(VS_Output ps_in) :COLOR0{
	return getDiffuseColor(ps_in.uv);
}

// �e�N�j�b�N
technique Tech {
	pass p0 {
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();

		// �A���t�@�u�����h���[�h
		AlphaBlendEnable = true;
		SrcBlend		 = SRCALPHA;
		DestBlend		 = INVSRCALPHA;
	}
}