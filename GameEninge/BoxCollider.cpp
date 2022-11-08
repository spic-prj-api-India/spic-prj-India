#include "BoxCollider.hpp"

namespace spic {
    float BoxCollider::Width() const { 
        return width; 
    }
    void BoxCollider::Width(float newWidth) { 
        width = newWidth; 
    }
    float BoxCollider::Height() const { 
        return height; 
    }
    void BoxCollider::Height(float newHeight) { 
        height = newHeight; 
    }
}