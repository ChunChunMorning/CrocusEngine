# pragma once
# include <unordered_map>
# include <Siv3D.hpp>

namespace cre
{
	using namespace s3d;

	Optional<XMLElement> FindChild(const XMLElement& element, const String& name);

	std::unordered_map<String, String> GetChildAsMap(const XMLElement& element);

	template <class Type>
	Optional<Type> GetArg(const XMLElement& element, const String& param)
	{
		const auto child = FindChild(element, param);

		if (!child)
		{
			LOG_ERROR(element.name(), L" : ˆø” \"", param, L"\" ‚ª‘«‚è‚Ü‚¹‚ñ.");

			return none;
		}

		const auto arg = ParseOpt<Type>(child.value().text());

		if (!arg.has_value())
		{
			LOG_ERROR(element.name(), L" : ˆø” \"", param, L"\" ‚ª³‚µ‚­‚ ‚è‚Ü‚¹‚ñ.");
		}

		return arg;
	}

	template <class Type>
	Optional<Type> GetArg(const XMLElement& element, const String& param, const Type& defaultValue)
	{
		const auto value = FindChild(element, param);

		if (!value.has_value())
		{
			return defaultValue;
		}

		const auto arg = ParseOpt<Type>(value.value().text());

		if (!arg.has_value())
		{
			LOG_ERROR(element.name(), L" : ˆø” \"", param, L"\" ‚ª³‚µ‚­‚ ‚è‚Ü‚¹‚ñ.");
		}

		return arg;
	}

	template <class Type>
	Array<Type> GetArrayArg(const XMLElement& element, const String& param)
	{
		auto parent = FindChild(element, param);

		if (!parent.has_value())
		{
			LOG_ERROR(element.name(), L" : ˆø” \"", param, L"\" ‚ª‚ ‚è‚Ü‚¹‚ñ.");
			return {};
		}

		auto child = parent.value().firstChild();

		if (child.isNull())
		{
			LOG_ERROR(element.name(), L" : ˆø” \"", param, L"\" ‚Éq—v‘f‚ª‚ ‚è‚Ü‚¹‚ñ.");
			return {};
		}

		Array<Type> arg;

		while (!child.isNull())
		{
			const auto e = ParseOpt<Type>(child.text());

			if (e.has_value())
			{
				arg.push_back(e.value());
			}
			else
			{
				LOG_ERROR(element.name(), L" : ˆø” \"", param, L"\" ‚Ì—v‘f‚ª³‚µ‚­‚ ‚è‚Ü‚¹‚ñ.");
			}

			child = child.nextSibling();
		}

		return arg;
	}

	template <class Type>
	Array<Type> GetArrayArg(const XMLElement& element, const String& param, const Array<Type>& defaultValue)
	{
		auto parent = FindChild(element, param);

		if (!parent.has_value())
		{
			return defaultValue;
		}

		auto child = parent.value().firstChild();

		if (child.isNull())
		{
			LOG_ERROR(element.name(), L" : ˆø” \"", param, L"\" ‚Éq—v‘f‚ª‚ ‚è‚Ü‚¹‚ñ.");
			return {};
		}

		Array<Type> arg;

		while (!child.isNull())
		{
			const auto e = ParseOpt<Type>(child.text());

			if (e.has_value())
			{
				arg.push_back(e.value());
			}
			else
			{
				LOG_ERROR(element.name(), L" : ˆø” \"", param, L"\" ‚Ì—v‘f‚ª³‚µ‚­‚ ‚è‚Ü‚¹‚ñ.");
			}

			child = child.nextSibling();
		}

		return arg;
	}
}
