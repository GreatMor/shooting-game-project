#include "GameModeMenuLvl.h"
#include "Menu/MenuPlayerController.h"
#include "Menu/UI/MenuHUD.h"


AGameModeMenuLvl::AGameModeMenuLvl()
{ 
	PlayerControllerClass = AMenuPlayerController::StaticClass();
	HUDClass = AMenuHUD::StaticClass();
}
