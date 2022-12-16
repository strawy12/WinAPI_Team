#pragma once
#pragma once
#include "Object.h"

class Image;
class Block : public Object
{
private:
    Image* m_pImage;
public:
    Block(MONSTER_TYPE type);
    virtual ~Block();
private:
    MONSTER_TYPE m_blockType;
public:
    void Update()       override;
    void Render(HDC _dc) override;

    CLONE(Block)
public:
    MONSTER_TYPE GetBlockType() { return m_blockType; }
};
