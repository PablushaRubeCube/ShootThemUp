#pragma once
#include"Player/STUPlayerState.h"

class STUUtils
{
public:
	template<typename T>
	 static T* GetSTUPlayerComponent(AActor* Char)
	{
		{
			if(!Char) return nullptr;
	
			auto Component = Char->GetComponentByClass(T::StaticClass());
		
			return Cast<T>(Component);
		}
	}


	static bool AreEnemy(AController* CallController, AController* EnemyController)
	{
		if (!CallController || !EnemyController || CallController == EnemyController) return false;

		const auto CallControllerPlayerState = Cast<ASTUPlayerState>(CallController->PlayerState);
		const auto EnemyControllerPlayerState = Cast<ASTUPlayerState>(EnemyController->PlayerState);

		return (CallControllerPlayerState && EnemyControllerPlayerState && CallControllerPlayerState->GetTeamID() != EnemyControllerPlayerState->GetTeamID());

	}
};





