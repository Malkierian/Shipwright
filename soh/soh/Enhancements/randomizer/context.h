#pragma once

#include "randomizerTypes.h"
#include "z64save.h"
#include "item_location.h"
#include "item_override.h"
#include "3drando/text.hpp"
#include "hint.h"

#include <memory>
#include <array>
#include <map>
#include <nlohmann/json.hpp>

/**
 * @brief Singleton for storing and accessing dynamic Randomizer-related data
 *
 * The Context class is a class for storing and accessing dynamic Randomizer-related data.
 * Dynamic Data, in this context, refers to data that can be different for each randomizer seed,
 * i.e. item locations, hint contents and locations, settings, etc. This class is intended to be
 * used as a Singleton.
 */
namespace Rando {
class EntranceShuffler;
class Logic;
class Settings;
class Dungeons;
class DungeonInfo;
class TrialInfo;
class Trials;

class Context {
  public:
    Context();
    static std::shared_ptr<Context> CreateInstance();
    static std::shared_ptr<Context> GetInstance();
    void InitStaticData();
    Hint* GetHint(RandomizerHintKey hintKey);
    void AddHint(RandomizerHintKey hintId, const Text& text, RandomizerCheck hintedLocation, HintType hintType, std::string distributionName,
                 RandomizerArea hintedArea = RA_NONE);
    ItemLocation* GetItemLocation(RandomizerCheck locKey);
    ItemLocation* GetItemLocation(size_t locKey);
    ItemOverride& GetItemOverride(RandomizerCheck locKey);
    ItemOverride& GetItemOverride(size_t locKey);
    void PlaceItemInLocation(RandomizerCheck locKey, RandomizerGet item, bool applyEffectImmediately = false,
                             bool setHidden = false);
    std::vector<RandomizerCheck> allLocations;
    void AddLocation(RandomizerCheck loc, std::vector<RandomizerCheck>* destination = nullptr);
    template <typename Container>
    void AddLocations(const Container& locations, std::vector<RandomizerCheck>* destination = nullptr);
    void GenerateLocationPool();
    static std::vector<RandomizerCheck> GetLocations(const std::vector<RandomizerCheck>& locationPool,
                                              Category categoryInclude, Category categoryExclude = Category::cNull);
    void AddExcludedOptions();
    void LocationReset();
    void ClearItemLocations();
    void ItemReset();
    void HintReset();
    void CreateItemOverrides();
    bool IsSeedGenerated() const;
    void SetSeedGenerated(bool seedGenerated = true);
    bool IsSpoilerLoaded() const;
    void SetSpoilerLoaded(bool spoilerLoaded = true);
    bool IsPlandoLoaded() const;
    void SetPlandoLoaded(bool plandoLoaded = true);
    void ApplyItemEffect(Item item, bool remove);
    std::shared_ptr<Settings> GetSettings();
    std::shared_ptr<EntranceShuffler> GetEntranceShuffler();
    std::shared_ptr<Dungeons> GetDungeons();
    DungeonInfo* GetDungeon(size_t key) const;
    std::shared_ptr<Logic> GetLogic();
    std::shared_ptr<SaveContext> GetSaveContext();
    void SetSaveContext(SaveContext* context);
    void ResetLogic();
    std::shared_ptr<Trials> GetTrials();
    TrialInfo* GetTrial(size_t key) const;
    static Sprite* GetSeedTexture(uint8_t index);
    Option& GetOption(RandomizerSettingKey key) const;
    TrickOption& GetTrickOption(RandomizerTrick key) const;
    GetItemEntry GetFinalGIEntry(RandomizerCheck rc, bool checkObtainability = true, GetItemID ogItemId = GI_NONE);
    void ParseSpoiler(const char* spoilerFileName, bool plandoMode);
    void ParseHashIconIndexesJson(nlohmann::json spoilerFileJson);
    void ParseItemLocationsJson(nlohmann::json spoilerFileJson);
    void ParseHintJson(nlohmann::json spoilerFileJson);
    std::map<RandomizerCheck, ItemOverride> overrides = {};
    std::vector<std::vector<RandomizerCheck>> playthroughLocations = {};
    std::vector<RandomizerCheck> everyPossibleLocation = {};
    std::vector<RandomizerGet> possibleIceTrapModels = {};
    std::unordered_map<RandomizerCheck, RandomizerGet> iceTrapModels = {};
    std::array<uint8_t, 5> hashIconIndexes = {};
    std::unordered_map<std::string, RandomizerCheck> mSpoilerfileCheckNameToEnum;
    bool playthroughBeatable = false;
    bool allLocationsReachable = false;
    RandomizerArea GetAreaFromString(std::string str);
    uint8_t InventorySlot(uint32_t item);
    void SetUpgrade(uint32_t upgrade, uint8_t level);
    uint32_t CurrentUpgrade(uint32_t upgrade);
    bool CheckInventory(uint32_t item, bool exact);
    void SetInventory(uint32_t itemSlot, uint32_t item);
    bool CheckEquipment(uint32_t item);
    bool CheckQuestItem(uint32_t item);
    void SetQuestItem(uint32_t item, bool remove);
    bool HasAdultTrade(uint32_t item);
    void SetAdultTrade(uint32_t item, bool remove);
    uint8_t GetSmallKeyCount(uint32_t dungeonIndex);
    void SetSmallKeyCount(uint32_t dungeonIndex, uint8_t count);
    bool CheckDungeonItem(uint32_t item, uint32_t dungeonIndex);
    void SetDungeonItem(uint32_t item, uint32_t dungeonIndex, bool remove);
    bool CheckRandoInf(uint32_t flag);
    void SetRandoInf(uint32_t flag, bool disable);
    bool CheckEventChkInf(int32_t flag);
    uint8_t GetGSCount();
    void SetEventChkInf(int32_t flag, bool disable);
    uint8_t GetAmmo(uint32_t item);
    void SetAmmo(uint32_t item, uint8_t count);

  private:
    static std::weak_ptr<Context> mContext;
    std::unordered_map<std::string, RandomizerGet> mSpoilerfileGetNameToEnum;
    std::unordered_map<std::string, HintType> mSpoilerfileHintTypeNameToEnum;
    std::unordered_map<std::string, RandomizerArea> mSpoilerfileAreaNameToEnum;
    std::array<Hint, RH_MAX> hintTable = {};
    RandomizerCheck mEmeraldLoc = RC_UNKNOWN_CHECK;
    RandomizerCheck mRubyLoc = RC_UNKNOWN_CHECK;
    RandomizerCheck mSapphireLoc = RC_UNKNOWN_CHECK;
    RandomizerCheck mForestMedallionLoc = RC_UNKNOWN_CHECK;
    RandomizerCheck mFireMedallionLoc = RC_UNKNOWN_CHECK;
    RandomizerCheck mWaterMedallionLoc = RC_UNKNOWN_CHECK;
    RandomizerCheck mShadowMedallionLoc = RC_UNKNOWN_CHECK;
    RandomizerCheck mSpiritMedallionLoc = RC_UNKNOWN_CHECK;
    RandomizerCheck mLightMedallionLoc = RC_UNKNOWN_CHECK;
    std::array<ItemLocation, RC_MAX> itemLocationTable = {};
    std::shared_ptr<Settings> mSettings;
    std::shared_ptr<EntranceShuffler> mEntranceShuffler;
    std::shared_ptr<Dungeons> mDungeons;
    std::shared_ptr<Logic> mLogic;
    std::shared_ptr<SaveContext> mSaveContext;
    std::shared_ptr<Trials> mTrials;
    bool mSeedGenerated = false;
    bool mSpoilerLoaded = false;
    bool mPlandoLoaded = false;
};
} // namespace Rando