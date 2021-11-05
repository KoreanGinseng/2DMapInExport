#include "ExporterMap2D.h"

using namespace Editor;

constexpr MofS8  Header[]  = "HEADER_DUMMY";
constexpr MofS32 HeaderLen = sizeof(Header);

enum class Map2DChunk : MofU8
{
    Texture,
    LayerData,
    CollisionData,

    Unknown = 0xFF,
};

/// <summary>
/// コンストラクタ
/// </summary>
CExporterMap2D::CExporterMap2D()
{
}

/// <summary>
/// デストラクタ
/// </summary>
CExporterMap2D::~CExporterMap2D()
{
}

/// <summary>
/// 出力
/// </summary>
/// <param name="file">ファイルパス</param>
/// <returns>TRUE : 成功, それ以外失敗</returns>
MofBool CExporterMap2D::Export(LPCMofChar file)
{
    struct ExportDataTexture
    {
        std::vector<std::string> names;
    };
    struct LayerData
    {
        std::string name      = "";
        MofS32      chipSize  = 16;
        MofS32      textureNo = -1;
    };
    struct ExportDataLayer
    {
        std::vector<LayerData> layers;
    };
    struct CollisionData
    {
        std::vector<CRectangle> rects;
    };
    struct ExportDataCollision
    {
        std::vector<CollisionData> collisions;
    };

    FILE* file_pointer = fopen(file, "wb");

    if (file_pointer == NULL)
    {
        return FALSE;
    }

    Map2DChunk chunk     = Map2DChunk::Unknown;
    MofS32     chunkSize = 0;

    // HEADER
    fwrite(Header, HeaderLen, 1, file_pointer);


    fclose(file_pointer);
    return TRUE;
}
