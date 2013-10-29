#pragma once

#include "BaseObject.h"

class BaseStaticObject : BaseObject
{
    public:
        virtual void Init() = 0;
        virtual void Cleanup() = 0;

        void Pause()
        {
            m_bPaused = true;
        }
        void Resume()
        {
            m_bPaused = false;
        }


        virtual void Update(GameEngine* game) = 0;
        virtual void Draw(GameEngine* game) = 0;

        virtual void Attack() = 0;
        void TakeDamage(int damage)
        {
            if( ! m_bInvulnerable )
            {
                m_iHealth -= damage;
            }
        }


    protected:
        BaseStaticObject(){}
    private:
        int m_iHealth;
        int m_iDefense;
        int m_iAttack;
        bool m_bAttacksFlying;
        bool m_bBlocksFlying;
        bool m_bInvulnerable;
        bool m_bPaused;

        GameLog logger;
};