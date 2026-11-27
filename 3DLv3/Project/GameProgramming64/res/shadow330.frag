#version 330 core
uniform vec3 lightVec;
uniform vec3 lightAmbientColor;
uniform vec3 lightDiffuseColor;
uniform vec3 eyeVec;
uniform vec4 Ambient;
uniform vec4 Diffuse;
uniform vec3 Specular;
uniform vec3 Emissive;
uniform float Pow;
uniform int TextureFlg;
uniform sampler2D Sampler;	//�e�N�X�`��
uniform sampler2DShadow DepthTexture;	//�f�v�X�e�N�X�`��

//���_�V�F�[�_�[����󂯎��ϐ�
in vec3 N;//�@���x�N�g��
in vec2 TexCoord0;	// ���_�V�F�[�_����󂯎��e�N�X�`�����W
in vec4 TexCoord1;	// ���_�V�F�[�_����󂯎��e�N�X�`�����W(DepthTexture�p)

//�o��
out vec4 FragColor;             // �o�͂���t���O�����g�̐F

void main() {
	float NL = dot(N, lightVec); 
	vec3 Reflect = normalize(2 * NL * N - lightVec);
	float specular = pow(clamp(dot(Reflect, eyeVec),0,1.0), Pow);

	vec4 texColor;
	if(TextureFlg == -1)
	{
		texColor = vec4(1.0,1.0,1.0,1.0);
	}
	else
	{
		texColor = texture(Sampler, TexCoord0);
	}
	//�f�v�X�e�N�X�`���̒l���擾
	float shd = textureProj(DepthTexture, TexCoord1);
	//�l��0�͉e�ɂ���
	if(shd == 0.0)
	{
		//texColor = texColor * 0.4; //�e�ɂ���
		texColor.w = 1.0;
	}
    // �e�N�X�`�����T���v�����O
	FragColor= texColor * (Diffuse * clamp(NL,0,1.0)* vec4(lightDiffuseColor,1.0)+ Ambient * vec4(lightAmbientColor,1.0) + vec4(specular*Specular + Emissive,1.0));
	FragColor.a = Diffuse.a;
}
