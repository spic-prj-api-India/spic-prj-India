#ifndef FLOCKING_H_
#define FLOCKING_H_

#include "Component.hpp"
#include <functional>
#include "ForceDriven.hpp"

namespace spic
{
    /**
     * @brief The base class for all colliders.
     */
    class Flocking : public Component {
    public:
        /**
         * @brief Constructor
         * @param agent 
        */
        Flocking(ForceDriven* agent);

        /**
         * @brief Constructor
         * @param agent 
         * @param viewRadius 
         * @param seperationWeight 
         * @param desiredSeparation 
         * @param alignmentWeight 
         * @param cohesionWeight 
        */
        Flocking(ForceDriven* agent, const float viewRadius, const  float seperationWeight, const float desiredSeparation,
            const float alignmentWeight, const float cohesionWeight);

        /**
         * @brief Activates seperation for force driven entity
         * @param seperationWeight The weight of the behaviour.
         * @param desiredSeparation The desperation space between force driven entities.
        */
        void SeperationOn(const float seperationWeight, const float desiredSeparation);

        /**
         * @brief Activates alignment for force driven entity.
         * @param alignmentWeight The weight of the behaviour.
         * @param viewRadius The radius where the entity searches for neighbors.
        */
        void AlignmentOn(const float alignmentWeight, const float viewRadius);

        /**
         * @brief Activates cohesion for force driven entity.
         * @param cohesionWeight The weight of the behaviour.
         * @param viewRadius The radius where the entity searches for neighbors.
        */
        void CohesionOn(const float cohesionWeight, const float viewRadius);

        /**
        * @brief Tags all nearby neigbors.
        * @param forceDrivenEntities The list of all force driven entities that are active.
        */
        void TagNeighbors(const std::vector<std::shared_ptr<ForceDriven>>& forceDrivenEntities);

        /**
        * @brief Calculates steering force.
        * @param addSteeringForceCallback Callback that adds forces to steering force.
        */
        void Calculate(std::function<bool(Point force)> addSteeringForceCallback);
    private:
        /**
       * @brief Calculates steering force to seperate from force driven entities.
       * @return spic::Point Steering force.
       */
        Point Seperate();

        /**
        * @brief Calculates steering force to align force driven entities.
        * @return spic::Point Steering force.
        */
        Point Align();

        /**
         * @brief Seek to target and return steering force.
         * @return spic::Point Steering force.
        */
        Point Seek(Point target);

        /**
        * @brief Calculates steering force to cohere force driven entities together.
        * @return spic::Point Steering force.
        */
        Point Cohere();
    private:
        /**
         * @brief agent used for flocking
        */
        const ForceDriven* agent;

        /**
         * @brief Neigbors of agent
        */
        std::vector<std::shared_ptr<ForceDriven>> neighbors;

        /**
         * @brief View radius of agent
        */
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