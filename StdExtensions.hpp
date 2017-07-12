#include <memory>

namespace std
{
	inline bool operator==(
		const std::weak_ptr<void> &a, const std::weak_ptr<void> &b)
	{
		return a.lock() == b.lock();
	}

	inline bool operator!=(
		const std::weak_ptr<void> &a, const std::weak_ptr<void> &b)
	{
		return !(a == b);
	}

	template <>
	struct hash<std::weak_ptr<void>>
	{
		std::size_t operator()(const std::weak_ptr<void> &val) const
		{
			auto shared = val.lock();
			if (shared)
			{
				auto hashVal = std::hash<decltype(shared)>()(shared);
				return hashVal;
			}
			else
			{
				return 0;
			}
		}
	};
}
