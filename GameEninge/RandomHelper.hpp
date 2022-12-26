#ifndef RANDOMHELPER_H_
#define RANDOMHELPER_H_

#include <random>
#include <mutex>

namespace spic::helper_functions
{
	template <bool is_integral, typename T> struct uniform_distribution_selector;

	template <typename T> struct uniform_distribution_selector<true, T>
	{
		using type = typename std::uniform_int_distribution<T>;
	};

	template <typename T> struct uniform_distribution_selector<false, T>
	{
		using type = typename std::uniform_real_distribution<T>;
	};

	/**
	 * @brief Contains  helpfull random functions
	*/ 
	class RandomHelper {
	private:
		static RandomHelper* pinstance_;
		static std::mutex mutex_;
		std::default_random_engine engine;
	protected:
		/**
		 * @brief Calls the init method
		*/
		RandomHelper();
		~RandomHelper() = default;
	public:
		RandomHelper(RandomHelper& other) = delete;
		RandomHelper(RandomHelper&& other) = delete;
		void operator=(const RandomHelper& other) = delete;
		RandomHelper& operator=(RandomHelper&& other) = delete;
		static RandomHelper* GetInstance();

		/**
		 * @brief Select random value between defined min and max value.
		 * @tparam T Type of the random value
		 * @param min Minimum value that random value needs to have.
		 * @param max Maximum value that random value needs to have.
		 * @return Random value
		*/
		template <typename R, typename T>
		R Between(T min, T max) {
			using uniform_distribution_type = typename uniform_distribution_selector<std::is_integral<T>::value, T>::type;
			uniform_distribution_type distribution(min, max);
			return static_cast<R>(distribution(engine));
		}

		/**
		 * @brief Selects random value from vector
		 * @tparam Iter Iterator type
		 * @param start Start iterator of vector
		 * @param end End iterator of vector
		 * @return Iterator of random value
		*/
		template<typename Iter>
		Iter SelectRandom(Iter start, Iter end) {
			std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
			std::advance(start, dis(engine));
			return start;
		}
	};
}

#endif // RANDOMHELPER_H_