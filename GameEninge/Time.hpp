#ifndef TIME_H_
#define TIME_H_

namespace spic {

    /**
     * @brief Class representing game time.
     */
    class Time {
        public:
            /**
             * @brief The interval in seconds from the last frame to the current one (Read Only)
             * TODO: no funtionality
             * @spicapi
             */
            static double DeltaTime();

            /**
             * @brief The scale at which time passes.
             * @return time scale value
             * @spicapi
             */
            static float TimeScale();

            /**
             * @brief The scale at which time passes.
             * @param newTimeScale The new value for the time scale.
             * @spicapi
             */
            static void TimeScale(const float newTimeScale);

        private:
            static double deltaTime;
            static float timeScale;
    };
}
#endif // TIME_H_