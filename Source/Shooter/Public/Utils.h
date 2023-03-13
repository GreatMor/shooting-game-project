#pragma once
class APawn;

class ShooterUtils
{
public:
	
	template<typename T>
	static T* GetShooterPLayerComponent(APawn* PlayerPawn)
	{
		if(PlayerPawn) return nullptr;
		const auto Player = PlayerPawn->GetComponentByClass(T::StaticClass());
		
		const auto Component = Player->GetComponentByClass(UHealthComponent::StaticClass());

		return Cast<T(Component);
	}
};