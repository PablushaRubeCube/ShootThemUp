#pragma once

class STUUtils
{
public:
	template<typename T>
	 static T* GetSTUPlayerComponent(APawn* Char)
	{
		{
			if(!Char) return nullptr;
	
			auto Component = Char->GetComponentByClass(T::StaticClass());
		
			return Cast<T>(Component);
		}
	}
};



