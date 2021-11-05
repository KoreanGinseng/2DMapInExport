#pragma once
#include <Mof.h>
#include <memory>
#include <string>
#include <vector>

namespace Editor
{
	/// <summary>
	/// ２Dマップバイナリ出力クラス
	/// </summary>
	class CExporterMap2D
	{
	public:

		/// <summary>
		/// コンストラクタ
		/// </summary>
		CExporterMap2D();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~CExporterMap2D();

		/// <summary>
		/// 出力
		/// </summary>
		/// <param name="file">ファイルパス</param>
		/// <returns>TRUE : 成功, それ以外失敗</returns>
		MofBool Export(LPCMofChar file);
	};
}

