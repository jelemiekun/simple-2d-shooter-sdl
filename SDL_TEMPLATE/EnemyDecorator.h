#pragma once
#include "Enemy.h"

class EnemyDecorator : public Enemy {
protected:
    std::shared_ptr<Enemy> decoratedEnemy;

public:
    EnemyDecorator(std::shared_ptr<Enemy> enemy);
    virtual void update() override;
    virtual void render() const override;
    virtual const bool& isDead() const override;
    virtual std::shared_ptr<Prototype> clone() const override;
};