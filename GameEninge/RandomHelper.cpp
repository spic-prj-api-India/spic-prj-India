#include "RandomHelper.hpp"

namespace spic::helper_functions
{
	RandomHelper* RandomHelper::pinstance_{ nullptr };
	std::mutex RandomHelper::mutex_;

	RandomHelper::RandomHelper() {
		std::random_device device;
		engine = std::default_random_engine(device());
	}

	RandomHelper* RandomHelper::GetInstance() {
		std::lock_guard<std::mutex> lock(mutex_);
		if (pinstance_ == nullptr)
			pinstance_ = new RandomHelper();

		return pinstance_;
	}
}