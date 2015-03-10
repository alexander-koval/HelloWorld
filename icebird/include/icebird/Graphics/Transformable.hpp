#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

#include <icebird/Graphics/Transform.hpp>


class Transformable {
public:
    Transformable();

    virtual ~Transformable();

    void setPosition(float x, float y);

    void setPosition(const Vector2F& position);

    void setRotation(float angle);

    void setScale(float factorX, float factorY);

    void setScale(const Vector2F& factors);

    void setOrigin(float x, float y);

    void setOrigin(const Vector2F& origin);

    const Vector2F& getPosition() const;

    float getRotation() const;

    const Vector2F& getScale() const;

    const Vector2F& getOrigin() const;

    void move(float offsetX, float offsetY);

    void move(const Vector2F& offset);

    void rotate(float angle);

    void scale(float factorX, float factorY);

    void scale(const Vector2F& factor);

    const Transform& getTransform() const;

    const Transform& getInverseTransform() const;

private:
    Vector2F          m_origin;
    Vector2F          m_position;
    float             m_rotation;
    Vector2F          m_scale;
    mutable Transform m_transform;
    mutable bool      m_transformNeedUpdate;
    mutable Transform m_inverseTransform;
    mutable bool      m_inverseTransformNeedUpdate;
};

#endif // TRANSFORMABLE_HPP
