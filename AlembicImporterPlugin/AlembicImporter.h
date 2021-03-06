#ifndef AlembicImporter_h
#define AlembicImporter_h

//// options
//#define aiWithTBB

#include "pch.h"



#ifdef _WIN32
typedef void (__stdcall *aiNodeEnumerator)(aiObject *node, void *userdata);
#else
typedef void (*aiNodeEnumerator)(aiObject *node, void *userdata);
#endif

struct aiV2 { float v[2]; };
struct aiV3 { float v[3]; };
struct aiM44 { float v[4][4]; };


struct aiSplitedMeshInfo
{
    int num_faces;
    int num_indices;
    int num_vertices;
    int begin_face;
    int begin_index;
    int triangulated_index_count;
};


aiCLinkage aiExport aiContext*      aiCreateContext();
aiCLinkage aiExport void            aiDestroyContext(aiContext* ctx);

aiCLinkage aiExport bool            aiLoad(aiContext* ctx, const char *path);
aiCLinkage aiExport float           aiGetStartTime(aiContext* ctx);
aiCLinkage aiExport float           aiGetEndTime(aiContext* ctx);
aiCLinkage aiExport aiObject*       aiGetTopObject(aiContext* ctx);

aiCLinkage aiExport void            aiEnumerateChild(aiObject *obj, aiNodeEnumerator e, void *userdata);
aiCLinkage aiExport const char*     aiGetNameS(aiObject* obj);
aiCLinkage aiExport const char*     aiGetFullNameS(aiObject* obj);
aiCLinkage aiExport uint32_t        aiGetNumChildren(aiObject* obj);
aiCLinkage aiExport void            aiSetCurrentTime(aiObject* obj, float time);
aiCLinkage aiExport void            aiEnableReverseX(aiObject* obj, bool v);
aiCLinkage aiExport void            aiEnableTriangulate(aiObject* obj, bool v);
aiCLinkage aiExport void            aiEnableReverseIndex(aiObject* obj, bool v);

aiCLinkage aiExport bool            aiHasXForm(aiObject* obj);
aiCLinkage aiExport bool            aiXFormGetInherits(aiObject* obj);
aiCLinkage aiExport aiV3            aiXFormGetPosition(aiObject* obj);
aiCLinkage aiExport aiV3            aiXFormGetAxis(aiObject* obj);
aiCLinkage aiExport float           aiXFormGetAngle(aiObject* obj);
aiCLinkage aiExport aiV3            aiXFormGetRotation(aiObject* obj);
aiCLinkage aiExport aiV3            aiXFormGetScale(aiObject* obj);
aiCLinkage aiExport aiM44           aiXFormGetMatrix(aiObject* obj);

aiCLinkage aiExport bool            aiHasPolyMesh(aiObject* obj);
aiCLinkage aiExport bool            aiPolyMeshIsTopologyConstant(aiObject* obj);
aiCLinkage aiExport bool            aiPolyMeshIsTopologyConstantTriangles(aiObject* obj);
aiCLinkage aiExport bool            aiPolyMeshHasNormals(aiObject* obj);
aiCLinkage aiExport bool            aiPolyMeshHasUVs(aiObject* obj);
aiCLinkage aiExport uint32_t        aiPolyMeshGetIndexCount(aiObject* obj);
aiCLinkage aiExport uint32_t        aiPolyMeshGetVertexCount(aiObject* obj);
aiCLinkage aiExport void            aiPolyMeshCopyIndices(aiObject* obj, int *dst);
aiCLinkage aiExport void            aiPolyMeshCopyVertices(aiObject* obj, abcV3 *dst);
aiCLinkage aiExport void            aiPolyMeshCopyNormals(aiObject* obj, abcV3 *dst);
aiCLinkage aiExport void            aiPolyMeshCopyUVs(aiObject* obj, abcV2 *dst);
aiCLinkage aiExport bool            aiPolyMeshGetSplitedMeshInfo(aiObject* obj, aiSplitedMeshInfo *o_smi, const aiSplitedMeshInfo *prev, int max_vertices);
aiCLinkage aiExport void            aiPolyMeshCopySplitedIndices(aiObject* obj, int *dst, const aiSplitedMeshInfo *smi);
aiCLinkage aiExport void            aiPolyMeshCopySplitedVertices(aiObject* obj, abcV3 *dst, const aiSplitedMeshInfo *smi);
aiCLinkage aiExport void            aiPolyMeshCopySplitedNormals(aiObject* obj, abcV3 *dst, const aiSplitedMeshInfo *smi);
aiCLinkage aiExport void            aiPolyMeshCopySplitedUVs(aiObject* obj, abcV2 *dst, const aiSplitedMeshInfo *smi);

struct aiTextureMeshData
{
    int num_indices;
    bool is_normal_indexed;
    bool is_uv_indexed;
    void *tex_indices;
    void *tex_vertices;
    void *tex_normals;
    void *tex_uvs;
};
aiCLinkage aiExport void            aiPolyMeshCopyDataToTexture(aiObject* obj, aiTextureMeshData *dst);


aiCLinkage aiExport bool            aiHasCurves(aiObject* obj);

aiCLinkage aiExport bool            aiHasPoints(aiObject* obj);

aiCLinkage aiExport bool            aiHasCamera(aiObject* obj);
aiCLinkage aiExport void            aiCameraGetParams(aiObject* obj, aiCameraParams *o_params);

aiCLinkage aiExport bool            aiHasLight(aiObject* obj);

aiCLinkage aiExport bool            aiHasMaterial(aiObject* obj);

#endif // AlembicImporter_h
