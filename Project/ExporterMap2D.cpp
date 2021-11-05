#include "ExporterMap2D.h"

using namespace Editor;

constexpr MofS8  Header[]  = "HEADER_DUMMY";
constexpr MofS32 HeaderLen = sizeof(Header);

enum class Map2DChunk : MofU8
{
    Texture,
    BackGround,
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
    struct LayerData
    {
        std::string name      = "";
        MofS32      chipSize  = 16;
        MofS32      textureNo = -1;
        std::vector<std::vector<MofS32>> mapData;
    };
    struct CollisionData
    {
        std::vector<CRectangle> rects;
    };
    struct BackGround
    {
        MofBool  alwaysScroll;
        MofFloat impact;
        MofFloat speed;
    };
    struct ExportDataBackGround
    {
        std::vector<BackGround> backgrounds;
    };
    struct ExportDataTexture
    {
        std::vector<std::string> names;
    };
    struct ExportDataLayer
    {
        std::vector<LayerData> layers;
    };
    struct ExportDataCollision
    {
        std::vector<CollisionData> collisions;
    };

    struct Exports
    {
        ExportDataBackGround background;
        ExportDataCollision  collision;
        ExportDataTexture    texture;
        ExportDataLayer      layer;
    };

    Exports exports;

    FILE* file_pointer = fopen(file, "wb");

    if (file_pointer == NULL)
    {
        return FALSE;
    }

    Map2DChunk chunk     = Map2DChunk::Unknown;
    MofS32     chunkSize = 0;

    // HEADER
    fwrite(Header, HeaderLen, 1, file_pointer);

    // TEXTURE
    if (exports.texture.names.size() > 0)
    {
        chunk     = Map2DChunk::Texture;
        chunkSize = 0;
        chunkSize += sizeof(MofS32);     // TEX COUNT
        for (const auto& name : exports.texture.names)
        {
            chunkSize += sizeof(MofS32); // NAME LEN
            chunkSize += name.length();  // NAME
        }
        // CHUNK DATA
        fwrite(&chunk, sizeof(Map2DChunk), 1, file_pointer);
        fwrite(&chunkSize, sizeof(MofS32), 1, file_pointer);
        // DATA
        MofS32 texCount = exports.texture.names.size();
        fwrite(&texCount, sizeof(MofS32), 1, file_pointer);
        for (const auto& name : exports.texture.names)
        {
            MofS32 nameLen = name.length();
            fwrite(&nameLen, sizeof(MofS32), 1, file_pointer);
            fwrite(name.c_str(), nameLen, 1, file_pointer);
        }
    }
    // LAYER
    if (exports.layer.layers.size() > 0)
    {
        chunk     = Map2DChunk::LayerData;
        chunkSize = 0;
        chunkSize += sizeof(MofS32);             // LAYER COUNT
        for (const auto& layer : exports.layer.layers)
        {
            chunkSize += sizeof(MofS32);         // NAME LEN
            chunkSize += layer.name.length();    // NAME
            chunkSize += sizeof(MofS32);         // CHIP SIZE
            chunkSize += sizeof(MofS32);         // TEX NO
            chunkSize += sizeof(MofS32);         // MAP ROW SIZE
            for (const auto& mapRow : layer.mapData)
            {
                chunkSize += sizeof(MofS32);     // MAP CULM SIZE
                for (const auto& mapData : mapRow)
                {
                    chunkSize += sizeof(MofS32); // MAPCHIPS
                }
            }
        }
    }

    fclose(file_pointer);
    return TRUE;
}
