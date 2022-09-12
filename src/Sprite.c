#include <QuickGame.h>
#include <Sprite.h>
#include <Types.h>
#include <stddef.h>
#include <gu2gl.h>

QGSprite* QuickGame_Sprite_Create(QGVector2 position, QGVector2 size, QGTexture* texture) {
    if(!texture)
        return NULL;

    QGSprite* sprite = QuickGame_Allocate(sizeof(QGSprite));
    if(!sprite)
        return NULL;

    sprite->transform.position = position;
    sprite->transform.scale = size;
    sprite->texture = texture;

    sprite->mesh = QuickGame_Graphics_Create_Mesh(QG_VERTEX_TYPE_TEXTURED, 4, 6);
    if(!sprite->mesh) {
        QuickGame_Destroy(sprite);
        return NULL;
    }

    QGTexturedVertex* verts = sprite->mesh->data;
    verts[0].u = 0.0f;
    verts[0].v = 0.0f;
    verts[0].color.color = 0xFFFFFFFF;
    verts[0].x = -0.5f;
    verts[0].y = -0.5f;
    verts[0].z = 0.0f;


    verts[1].u = 1.0f;
    verts[1].v = 0.0f;
    verts[1].color.color = 0xFFFFFFFF;
    verts[1].x = 0.5f;
    verts[1].y = -0.5f;
    verts[1].z = 0.0f;


    verts[2].u = 1.0f;
    verts[2].v = 1.0f;
    verts[2].color.color = 0xFFFFFFFF;
    verts[2].x = 0.5f;
    verts[2].y = 0.5f;
    verts[2].z = 0.0f;


    verts[3].u = 0.0f;
    verts[3].v = 1.0f;
    verts[3].color.color = 0xFFFFFFFF;
    verts[3].x = -0.5f;
    verts[3].y = 0.5f;
    verts[3].z = 0.0f;

    u16* indices = sprite->mesh->indices;
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;

    return sprite;
}

/**
 * @brief Destroy a sprite and sets it to NULL
 * 
 * @param sprite Pointer to Sprite
 */
void QuickGame_Sprite_Destroy(QGSprite** sprite) {
    if(sprite != NULL)
        return;
    
    QuickGame_Graphics_Destroy_Mesh(&(*sprite)->mesh);
    QuickGame_Destroy((*sprite));
    *sprite = NULL;
}

/**
 * @brief 
 * 
 * @param sprite 
 */
void QuickGame_Sprite_Draw(QGSprite* sprite) {
    if(!sprite)
        return;

    glMatrixMode(GL_MODEL);
    glLoadIdentity();

    ScePspFVector3 v = {sprite->transform.scale.x, sprite->transform.scale.y, 1.0f};
    gluScale(&v); 
    gluRotateZ(sprite->transform.rotation);
    ScePspFVector3 v1 = {sprite->transform.position.x, sprite->transform.position.y, sprite->layer};
    gluTranslate(&v1);

    QuickGame_Texture_Bind(sprite->texture);
    QuickGame_Graphics_Draw_Mesh(sprite->mesh);
    QuickGame_Texture_Unbind(sprite->texture);

    glLoadIdentity();
}