
#include "CesiumCreditSystem.h"
#include "UnrealConversions.h"
#include "Cesium3DTiles/CreditSystem.h"
#include <string>

/*static*/ ACesiumCreditSystem* ACesiumCreditSystem::GetDefaultForActor(AActor* Actor) {
    ACesiumCreditSystem* pACreditSystem = FindObject<ACesiumCreditSystem>(Actor->GetLevel(), TEXT("CesiumCreditSystemDefault"));
    if (!pACreditSystem) {
        FActorSpawnParameters spawnParameters;
        spawnParameters.Name = TEXT("CesiumCreditSystemDefault");
        spawnParameters.OverrideLevel = Actor->GetLevel();
        pACreditSystem = Actor->GetWorld()->SpawnActor<ACesiumCreditSystem>(spawnParameters);
    }
    return pACreditSystem;
}

ACesiumCreditSystem::ACesiumCreditSystem() {
    PrimaryActorTick.bCanEverTick = true;
    _pCreditSystem = std::make_shared<Cesium3DTiles::CreditSystem>();
}

ACesiumCreditSystem::~ACesiumCreditSystem() {
    _pCreditSystem.reset();
}

bool ACesiumCreditSystem::ShouldTickIfViewportsOnly() const {
    return true;
}

void ACesiumCreditSystem::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    std::string creditString = 
        "<head>\n<meta charset=\"utf-16\"/>\n</head>\n" + 
        this->_pCreditSystem->getHtmlPageToShowThisFrame();
    Credits = utf8_to_wstr(creditString);
    _pCreditSystem->startNextFrame();
}

void ACesiumCreditSystem::OnConstruction(const FTransform& Transform) {}