#pragma once
#pragma once
#include "Object.h"

class Image;
class Block : public Object
{
public:
    Block(MONSTER_TYPE type);
    virtual ~Block();

public:
    void Update()       override;
    void Render(HDC _dc) override;
    CLONE(Block)

public:
    MONSTER_TYPE GetBlockType() { return m_blockType; }
private:
    Image* m_pImage;
    MONSTER_TYPE m_blockType;
    BLENDFUNCTION m_bf = {};

};
