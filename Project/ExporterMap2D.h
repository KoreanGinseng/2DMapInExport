#pragma once
#include <Mof.h>
#include <memory>
#include <string>
#include <vector>

namespace Editor
{
	/// <summary>
	/// �QD�}�b�v�o�C�i���o�̓N���X
	/// </summary>
	class CExporterMap2D
	{
	public:

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		CExporterMap2D();

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~CExporterMap2D();

		/// <summary>
		/// �o��
		/// </summary>
		/// <param name="file">�t�@�C���p�X</param>
		/// <returns>TRUE : ����, ����ȊO���s</returns>
		MofBool Export(LPCMofChar file);
	};
}

