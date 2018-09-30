#pragma once

namespace thesis {
	class DefaultPlateDelegate {
	public:
		virtual ~DefaultPlateDelegate() {}

		virtual void defaultDraw() const = 0;
		virtual void defaultDrawForPicking() const = 0;
	};

} /* namespace thesis */