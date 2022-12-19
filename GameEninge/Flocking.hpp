#ifndef FLOCKING_H_
#define FLOCKING_H_

#include "Component.hpp"
#include <functional>
#include "ForceDriven.hpp"

namespace spic {
    /**
     * @brief The base class for all colliders.
     * @spicapi
     */
    class Flocking : public Component {
    public:
        Flocking(ForceDriven* agent);
        Flocking(ForceDriven* agent, const float viewRadius, const  float seperationWeight, const float desiredSeparation,
            const float alignmentWeight, const float cohesionWeight);

        /**
         * @brief Activates seperation for force driven entity
         * @param seperationWeight The weight of the behaviour.
         * @param desiredSeparation The desperation space between force driven entities.
         * @spicapi
        */
        void SeperationOn(const float seperationWeight, const float desiredSeparation);

        /**
         * @brief Activates alignment for force driven entity.
         * @param alignmentWeight The weight of the behaviour.
         * @param viewRadius The radius where the entity searches for neighbors.
         * @spicapi
        */
        void AlignmentOn(const float alignmentWeight, const float viewRadius);

        /**
         * @brief Activates cohesion for force driven entity.
         * @param cohesionWeight The weight of the behaviour.
         * @param viewRadius The radius where the entity searches for neighbors.
         * @spicapi
        */
        void CohesionOn(const float cohesionWeight, const float viewRadius);

        /**
        * @brief Tags all nearby neigbors.
        * @param forceDrivenEntities The list of all force driven entities that are active.
        * @spicapi
        */
        void TagNeighbors(const std::vector<std::shared_ptr<ForceDriven>>& forceDrivenEntities);

        /**
        * @brief Calculates steering force.
        * @param addSteeringForceCallback Callback that adds forces to steering force.
        * @spicapi
        */
        void Calculate(std::function<bool(Point force)> addSteeringForceCallback);
    private:
        /**
       * @brief Calculates steering force to seperate from force driven entities.
       * @return spic::Point Steering force.
       * @spicapi
       */
        Point Seperate();

        /**
        * @brief Calculates steering force to align force driven entities.
        * @return spic::Point Steering force.
        * @spicapi
        */
        Point Align();

        /**
         * @brief Seek to target and return steering force.
         * @return spic::Point Steering force.
         * @spicapi
        */
        Point Seek(Point target);

        /**
        * @brief Calculates steering force to cohere force driven entities together.
        * @return spic::Point Steering force.
        * @spicapi
        */
        Point Cohere();
    private:
        const ForceDriven* agent;
        std::vector<std::shared_ptr<ForceDriven>> neighbors;
        float viewRadius;

        /**
        * @brief Seperation properties.
        */
        bool useSeperation;
        float seperationWeight;
        float desiredSeparation;

        /**
        * @brief Alignment properties.
        */
        bool useAlignment;
        float alignmentWeight;

        /**
        * @brief Cohesion properties.
        */
        bool useCohesion;
        float cohesionWeight;
    };
}

#endif // FLOCKING_H_