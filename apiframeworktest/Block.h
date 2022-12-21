#pragma once
#pragma once
#include "Object.h"

class Image;
class Block : public Object
{
public:
    Block(BOX_TYPE type);
    virtual ~Block();

public:
    void Update()       override;
    void Render(HDC _dc) override;
    CLONE(Block)

public:
    BOX_TYPE GetBlockType() { return m_blockType; }
private:
    Image* m_pImage;
    BOX_TYPE m_blockType;
    BLENDFUNCTION m_bf = {};

};
