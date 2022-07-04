#pragma once

class AnimUtils
{
public:
	AnimUtils();
	~AnimUtils();

	template <typename T>
	static T* FindNotifyByClass(UAnimSequenceBase* Anim)
	{
		if (!Anim) return nullptr;

		const auto Notifies = Anim->Notifies;
		for (auto NotifyInst : Notifies)
		{
			auto CurrentNotify = Cast<T>(NotifyInst.Notify);
			if (CurrentNotify)
			{
				return CurrentNotify;
			}
		}
		return nullptr;
	}; 

private:

};

AnimUtils::AnimUtils()
{
}

AnimUtils::~AnimUtils()
{
}