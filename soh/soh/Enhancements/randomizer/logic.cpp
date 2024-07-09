#include "logic.h"

#include <algorithm>
#include <cstdio>
#include <string>
#include <string_view>
#include <vector>

#include "dungeon.h"
#include "context.h"
#include <spdlog/spdlog.h>

namespace Rando {
    bool Logic::IsMagicItem(RandomizerGet item) {
        return item == RG_DINS_FIRE    ||
                item == RG_FARORES_WIND ||
                item == RG_NAYRUS_LOVE  ||
                item == RG_LENS_OF_TRUTH;
    }

    bool Logic::IsMagicArrow(RandomizerGet item) {
        return item == RG_FIRE_ARROWS ||
                item == RG_ICE_ARROWS  ||
                item == RG_LIGHT_ARROWS;
    }

    bool Logic::HasItem2(RandomizerGet itemName) {
        return  (itemName == RG_DINS_FIRE              && DinsFire)            ||
                (itemName == RG_FARORES_WIND           && FaroresWind)         ||
                (itemName == RG_NAYRUS_LOVE            && NayrusLove)          ||
                (itemName == RG_LENS_OF_TRUTH          && LensOfTruth)         ||
                (itemName == RG_FAIRY_BOW              && Bow)                 ||
                (itemName == RG_MEGATON_HAMMER         && Hammer)              ||
                (itemName == RG_IRON_BOOTS             && IronBoots)           ||
                (itemName == RG_HOVER_BOOTS            && HoverBoots)          ||
                (itemName == RG_HOOKSHOT               && Hookshot)            ||
                (itemName == RG_LONGSHOT               && Longshot)            ||
                (itemName == RG_SILVER_GAUNTLETS       && SilverGauntlets)     ||
                (itemName == RG_GOLDEN_GAUNTLETS       && GoldenGauntlets)     ||
                (itemName == RG_GORON_TUNIC            && GoronTunic)          ||
                (itemName == RG_ZORA_TUNIC             && ZoraTunic)           ||
                (itemName == RG_SCARECROW              && Scarecrow)           ||
                (itemName == RG_DISTANT_SCARECROW      && DistantScarecrow)    ||
                (itemName == RG_HYLIAN_SHIELD          && HylianShield)        ||
                (itemName == RG_MIRROR_SHIELD          && MirrorShield)        ||
                (itemName == RG_MASTER_SWORD           && MasterSword)         ||
                (itemName == RG_BIGGORON_SWORD         && BiggoronSword)       ||
                (itemName == RG_FAIRY_SLINGSHOT        && Slingshot)           ||
                (itemName == RG_BOOMERANG              && Boomerang)           ||
                (itemName == RG_KOKIRI_SWORD           && KokiriSword)         ||
                (itemName == RG_STICKS                 && Sticks)              ||
                (itemName == RG_DEKU_SHIELD            && DekuShield)          ||
                (itemName == RG_FIRE_ARROWS            && FireArrows)          ||
                (itemName == RG_ICE_ARROWS             && IceArrows)           ||
                (itemName == RG_LIGHT_ARROWS           && LightArrows)         ||
                (itemName == RG_OCARINA_A_BUTTON       && OcarinaAButton)      ||
                (itemName == RG_OCARINA_C_LEFT_BUTTON  && OcarinaCLeftButton)  ||
                (itemName == RG_OCARINA_C_RIGHT_BUTTON && OcarinaCRightButton) ||
                (itemName == RG_OCARINA_C_DOWN_BUTTON  && OcarinaCDownButton)  ||
                (itemName == RG_OCARINA_C_UP_BUTTON    && OcarinaCUpButton)    ||
                (itemName == RG_FISHING_POLE           && FishingPole)         ||
                (itemName == RG_ZELDAS_LULLABY         && ZeldasLullaby)       ||
                (itemName == RG_EPONAS_SONG            && EponasSong)          ||
                (itemName == RG_SARIAS_SONG            && SariasSong)          ||
                (itemName == RG_SUNS_SONG              && SunsSong)            ||
                (itemName == RG_SONG_OF_TIME           && SongOfTime)          ||
                (itemName == RG_SONG_OF_STORMS         && SongOfStorms)        ||
                (itemName == RG_MINUET_OF_FOREST       && MinuetOfForest)      ||
                (itemName == RG_BOLERO_OF_FIRE         && BoleroOfFire)        ||
                (itemName == RG_SERENADE_OF_WATER      && SerenadeOfWater)     ||
                (itemName == RG_REQUIEM_OF_SPIRIT      && RequiemOfSpirit)     ||
                (itemName == RG_NOCTURNE_OF_SHADOW     && NocturneOfShadow)    ||
                (itemName == RG_PRELUDE_OF_LIGHT       && PreludeOfLight);
    }

    bool Logic::HasItem(RandomizerGet itemName) {
        bool has3 = HasItem3(itemName);
        //if (itemName >= RG_BOOMERANG && itemName <= RG_CLAIM_CHECK)
        //    SPDLOG_INFO("HasItem for {} evaluated as {}", StaticData::RetrieveItem(itemName).GetName().GetEnglish().c_str(), has3 ? "true" : "false");
        return has3;
    }

    bool Logic::HasItem3(RandomizerGet itemName) {
        return  (itemName == RG_DINS_FIRE              && ctx->CheckInventory(ITEM_DINS_FIRE, true))            ||
                (itemName == RG_FARORES_WIND           && ctx->CheckInventory(ITEM_FARORES_WIND, true))         ||
                (itemName == RG_NAYRUS_LOVE            && ctx->CheckInventory(ITEM_NAYRUS_LOVE, true))          ||
                (itemName == RG_LENS_OF_TRUTH          && ctx->CheckInventory(ITEM_LENS, true))         ||
                (itemName == RG_FAIRY_BOW              && ctx->CheckInventory(ITEM_BOW, true))                 ||
                (itemName == RG_MEGATON_HAMMER         && ctx->CheckInventory(ITEM_HAMMER, true))              ||
                (itemName == RG_IRON_BOOTS             && ctx->CheckEquipment(EQUIP_FLAG_BOOTS_IRON))           ||
                (itemName == RG_HOVER_BOOTS            && ctx->CheckEquipment(EQUIP_FLAG_BOOTS_HOVER))          ||
                (itemName == RG_HOOKSHOT               && ctx->CheckInventory(ITEM_HOOKSHOT, false))            ||
                (itemName == RG_LONGSHOT               && ctx->CheckInventory(ITEM_LONGSHOT, true))            ||
                (itemName == RG_GORONS_BRACELET        && ctx->CurrentUpgrade(UPG_STRENGTH) >= 1) || 
                (itemName == RG_SILVER_GAUNTLETS       && ctx->CurrentUpgrade(UPG_STRENGTH) >= 2) || 
                (itemName == RG_GOLDEN_GAUNTLETS       && ctx->CurrentUpgrade(UPG_STRENGTH) == 3)     ||
                (itemName == RG_GORON_TUNIC            && ctx->CheckEquipment(EQUIP_FLAG_TUNIC_GORON))          ||
                (itemName == RG_ZORA_TUNIC             && ctx->CheckEquipment(EQUIP_FLAG_TUNIC_ZORA))           ||
                (itemName == RG_SCARECROW              && Scarecrow)           ||
                (itemName == RG_DISTANT_SCARECROW      && DistantScarecrow)    ||
                (itemName == RG_HYLIAN_SHIELD          && ctx->CheckEquipment(EQUIP_FLAG_SHIELD_HYLIAN))        ||
                (itemName == RG_MIRROR_SHIELD          && ctx->CheckEquipment(EQUIP_FLAG_SHIELD_MIRROR))        ||
                (itemName == RG_MASTER_SWORD           && ctx->CheckEquipment(EQUIP_FLAG_SWORD_MASTER))         ||
                (itemName == RG_BIGGORON_SWORD         && ctx->CheckEquipment(EQUIP_FLAG_SWORD_BGS) && ctx->GetSaveContext()->bgsFlag)       ||
                (itemName == RG_FAIRY_SLINGSHOT        && ctx->CheckInventory(ITEM_SLINGSHOT, true))           ||
                (itemName == RG_BOOMERANG              && ctx->CheckInventory(ITEM_BOOMERANG, true))           ||
                (itemName == RG_BOMB_BAG               && ctx->CurrentUpgrade(UPG_BOMB_BAG) >= 1)           ||
                (itemName == RG_MAGIC_SINGLE           && ctx->GetSaveContext()->magicLevel >= 1)           ||
                (itemName == RG_KOKIRI_SWORD           && ctx->CheckEquipment(EQUIP_FLAG_SWORD_KOKIRI))         ||
                (itemName == RG_STICKS                 && ctx->CheckInventory(ITEM_STICK, true))              ||
                (itemName == RG_DEKU_SHIELD            && ctx->CheckEquipment(EQUIP_FLAG_SHIELD_DEKU))          ||
                (itemName == RG_FIRE_ARROWS            && ctx->CheckInventory(ITEM_ARROW_FIRE, true))          ||
                (itemName == RG_ICE_ARROWS             && ctx->CheckInventory(ITEM_ARROW_ICE, true))           ||
                (itemName == RG_LIGHT_ARROWS           && ctx->CheckInventory(ITEM_ARROW_LIGHT, true))         ||
                (itemName == RG_PROGRESSIVE_BOMBCHUS   && ctx->CheckInventory(ITEM_BOMBCHU, true))         ||
                (itemName == RG_FISHING_POLE           && ctx->CheckRandoInf(RAND_INF_FISHING_POLE_FOUND))         ||
                (itemName == RG_ZELDAS_LULLABY         && ctx->CheckQuestItem(QUEST_SONG_LULLABY))       ||
                (itemName == RG_EPONAS_SONG            && ctx->CheckQuestItem(QUEST_SONG_EPONA))          ||
                (itemName == RG_SARIAS_SONG            && ctx->CheckQuestItem(QUEST_SONG_SARIA))          ||
                (itemName == RG_SUNS_SONG              && ctx->CheckQuestItem(QUEST_SONG_SUN))            ||
                (itemName == RG_SONG_OF_TIME           && ctx->CheckQuestItem(QUEST_SONG_TIME))          ||
                (itemName == RG_SONG_OF_STORMS         && ctx->CheckQuestItem(QUEST_SONG_STORMS))        ||
                (itemName == RG_MINUET_OF_FOREST       && ctx->CheckQuestItem(QUEST_SONG_MINUET))      ||
                (itemName == RG_BOLERO_OF_FIRE         && ctx->CheckQuestItem(QUEST_SONG_BOLERO))        ||
                (itemName == RG_SERENADE_OF_WATER      && ctx->CheckQuestItem(QUEST_SONG_SERENADE))     ||
                (itemName == RG_REQUIEM_OF_SPIRIT      && ctx->CheckQuestItem(QUEST_SONG_REQUIEM))     ||
                (itemName == RG_NOCTURNE_OF_SHADOW     && ctx->CheckQuestItem(QUEST_SONG_NOCTURNE))    ||
                (itemName == RG_PRELUDE_OF_LIGHT       && ctx->CheckQuestItem(QUEST_SONG_PRELUDE))     ||
                (itemName == RG_ZELDAS_LETTER          && ctx->CheckRandoInf(RAND_INF_ZELDAS_LETTER))     ||
                (itemName == RG_RUTOS_LETTER           && ctx->CheckEventChkInf(EVENTCHKINF_OBTAINED_RUTOS_LETTER))     ||
                (itemName == RG_WEIRD_EGG              && ctx->CheckRandoInf(RAND_INF_WEIRD_EGG))                   ||
                (itemName == RG_STONE_OF_AGONY         && ctx->CheckQuestItem(QUEST_STONE_OF_AGONY))    ||
                (itemName == RG_FAIRY_OCARINA          && ctx->CheckInventory(ITEM_OCARINA_FAIRY, false)) ||
                (itemName == RG_OCARINA_OF_TIME        && ctx->CheckInventory(ITEM_OCARINA_TIME, true)) ||
                (itemName == RG_GREG_RUPEE             && ctx->CheckRandoInf(RAND_INF_GREG_FOUND))    ||
                (itemName == RG_GERUDO_MEMBERSHIP_CARD && ctx->CheckQuestItem(QUEST_GERUDO_CARD))    ||
                (itemName == RG_DOUBLE_DEFENSE         && ctx->GetSaveContext()->isDoubleDefenseAcquired) ||
                // Dungeon Rewards
                (itemName == RG_KOKIRI_EMERALD         && ctx->CheckQuestItem(QUEST_KOKIRI_EMERALD)) ||
                (itemName == RG_GORON_RUBY             && ctx->CheckQuestItem(QUEST_GORON_RUBY)) ||
                (itemName == RG_ZORA_SAPPHIRE          && ctx->CheckQuestItem(QUEST_ZORA_SAPPHIRE)) ||
                (itemName == RG_FOREST_MEDALLION       && ctx->CheckQuestItem(QUEST_MEDALLION_FOREST)) ||
                (itemName == RG_FIRE_MEDALLION         && ctx->CheckQuestItem(QUEST_MEDALLION_FIRE)) ||
                (itemName == RG_WATER_MEDALLION        && ctx->CheckQuestItem(QUEST_MEDALLION_WATER)) ||
                (itemName == RG_SPIRIT_MEDALLION       && ctx->CheckQuestItem(QUEST_MEDALLION_SPIRIT)) ||
                (itemName == RG_SHADOW_MEDALLION       && ctx->CheckQuestItem(QUEST_MEDALLION_SHADOW)) ||
                (itemName == RG_LIGHT_MEDALLION        && ctx->CheckQuestItem(QUEST_MEDALLION_LIGHT)) ||
                // Ocarina Buttons
                (itemName == RG_OCARINA_A_BUTTON       && ctx->CheckRandoInf(RAND_INF_HAS_OCARINA_A))      ||
                (itemName == RG_OCARINA_C_LEFT_BUTTON  && ctx->CheckRandoInf(RAND_INF_HAS_OCARINA_C_LEFT))  ||
                (itemName == RG_OCARINA_C_RIGHT_BUTTON && ctx->CheckRandoInf(RAND_INF_HAS_OCARINA_C_RIGHT)) ||
                (itemName == RG_OCARINA_C_DOWN_BUTTON  && ctx->CheckRandoInf(RAND_INF_HAS_OCARINA_C_DOWN))  ||
                (itemName == RG_OCARINA_C_UP_BUTTON    && ctx->CheckRandoInf(RAND_INF_HAS_OCARINA_C_UP))  ||
                // Boss Souls
                (itemName == RG_GOHMA_SOUL             && ctx->CheckRandoInf(RAND_INF_GOHMA_SOUL)) ||
                (itemName == RG_KING_DODONGO_SOUL      && ctx->CheckRandoInf(RAND_INF_KING_DODONGO_SOUL))  ||
                (itemName == RG_BARINADE_SOUL          && ctx->CheckRandoInf(RAND_INF_BARINADE_SOUL))  ||
                (itemName == RG_PHANTOM_GANON_SOUL     && ctx->CheckRandoInf(RAND_INF_PHANTOM_GANON_SOUL))  ||
                (itemName == RG_VOLVAGIA_SOUL          && ctx->CheckRandoInf(RAND_INF_VOLVAGIA_SOUL))  ||
                (itemName == RG_MORPHA_SOUL            && ctx->CheckRandoInf(RAND_INF_MORPHA_SOUL))  ||
                (itemName == RG_BONGO_BONGO_SOUL       && ctx->CheckRandoInf(RAND_INF_BONGO_BONGO_SOUL))  ||
                (itemName == RG_TWINROVA_SOUL          && ctx->CheckRandoInf(RAND_INF_TWINROVA_SOUL))  ||
                (itemName == RG_GANON_SOUL             && ctx->CheckRandoInf(RAND_INF_GANON_SOUL)) ||
                // Boss Keys
                (itemName == RG_FOREST_TEMPLE_BOSS_KEY && ctx->CheckDungeonItem(DUNGEON_KEY_BOSS, SCENE_FOREST_TEMPLE)) ||
                (itemName == RG_FIRE_TEMPLE_BOSS_KEY   && ctx->CheckDungeonItem(DUNGEON_KEY_BOSS, SCENE_FIRE_TEMPLE)) ||
                (itemName == RG_WATER_TEMPLE_BOSS_KEY  && ctx->CheckDungeonItem(DUNGEON_KEY_BOSS, SCENE_WATER_TEMPLE)) ||
                (itemName == RG_SPIRIT_TEMPLE_BOSS_KEY && ctx->CheckDungeonItem(DUNGEON_KEY_BOSS, SCENE_SPIRIT_TEMPLE)) ||
                (itemName == RG_SHADOW_TEMPLE_BOSS_KEY && ctx->CheckDungeonItem(DUNGEON_KEY_BOSS, SCENE_SHADOW_TEMPLE)) ||
                (itemName == RG_GANONS_CASTLE_BOSS_KEY && ctx->CheckDungeonItem(DUNGEON_KEY_BOSS, SCENE_INSIDE_GANONS_CASTLE)) ||
                // Wallets
                (itemName == RG_CHILD_WALLET           && ctx->CheckRandoInf(RAND_INF_HAS_WALLET)) ||
                (itemName == RG_ADULT_WALLET           && ctx->CurrentUpgrade(UPG_WALLET) >= 1) ||
                (itemName == RG_GIANT_WALLET           && ctx->CurrentUpgrade(UPG_WALLET) >= 2) ||
                (itemName == RG_TYCOON_WALLET          && ctx->CurrentUpgrade(UPG_WALLET) >= 3) ||
                // Scales
                (itemName == RG_BRONZE_SCALE           && ctx->CheckRandoInf(RAND_INF_CAN_SWIM)) ||
                (itemName == RG_SILVER_SCALE           && ctx->CurrentUpgrade(UPG_SCALE) >= 1) ||
                (itemName == RG_GOLDEN_SCALE           && ctx->CurrentUpgrade(UPG_SCALE) >= 2);
    }

    //Can the passed in item be used?
    bool Logic::CanUse(RandomizerGet itemName) {
        if (!HasItem(itemName))
            return false;

        switch (itemName) {
            // Adult items
            // TODO: Uncomment those if we ever implement more item usability settings
            case RG_FAIRY_BOW:
                return IsAdult;// || BowAsChild;
            case RG_MEGATON_HAMMER:
                return IsAdult;// || HammerAsChild;
            case RG_IRON_BOOTS:
                return IsAdult;// || IronBootsAsChild;
            case RG_HOVER_BOOTS:
                return IsAdult;// || HoverBootsAsChild;
            case RG_HOOKSHOT:
                return IsAdult;// || HookshotAsChild;
            case RG_LONGSHOT:
                return IsAdult;// || HookshotAsChild;
            case RG_SILVER_GAUNTLETS:
                return IsAdult;
            case RG_GOLDEN_GAUNTLETS:
                return IsAdult;
            case RG_GORON_TUNIC:
                return IsAdult;// || GoronTunicAsChild;
            case RG_ZORA_TUNIC:
                return IsAdult;// || ZoraTunicAsChild;
            case RG_SCARECROW:
                return IsAdult;// || HookshotAsChild;
            case RG_DISTANT_SCARECROW:
                return IsAdult;// || HookshotAsChild;
            case RG_HYLIAN_SHIELD:
                return IsAdult;
            case RG_MIRROR_SHIELD:
                return IsAdult;// || MirrorShieldAsChild;
            case RG_MASTER_SWORD:
                return IsAdult;// || MasterSwordAsChild;
            case RG_BIGGORON_SWORD:
                return IsAdult;// || BiggoronSwordAsChild;

            // Child items
            case RG_FAIRY_SLINGSHOT:
                return IsChild;// || SlingshotAsAdult;
            case RG_BOOMERANG:
                return IsChild;// || BoomerangAsAdult;
            case RG_KOKIRI_SWORD:
                return IsChild;// || KokiriSwordAsAdult;
            case RG_STICKS:
                return IsChild;// || StickAsAdult;
            case RG_DEKU_SHIELD:
                return IsChild;// || DekuShieldAsAdult;
            case RG_WEIRD_EGG:
                return IsChild;
            case RG_RUTOS_LETTER:
                return IsChild;

            // Songs
            case RG_ZELDAS_LULLABY:
                return Ocarina && OcarinaCLeftButton && OcarinaCRightButton && OcarinaCUpButton;
            case RG_EPONAS_SONG:
                return Ocarina && OcarinaCLeftButton && OcarinaCRightButton && OcarinaCUpButton;
            case RG_SARIAS_SONG:
                return Ocarina && OcarinaCLeftButton && OcarinaCRightButton && OcarinaCDownButton;
            case RG_SUNS_SONG:
                return Ocarina && OcarinaCRightButton && OcarinaCUpButton && OcarinaCDownButton;
            case RG_SONG_OF_TIME:
                return Ocarina && OcarinaAButton && OcarinaCRightButton && OcarinaCDownButton;
            case RG_SONG_OF_STORMS:
                return Ocarina && OcarinaAButton && OcarinaCUpButton && OcarinaCDownButton;
            case RG_MINUET_OF_FOREST:
                return Ocarina && OcarinaAButton && OcarinaCLeftButton && OcarinaCRightButton && OcarinaCUpButton;
            case RG_BOLERO_OF_FIRE:
                return Ocarina && OcarinaAButton && OcarinaCRightButton && OcarinaCDownButton;
            case RG_SERENADE_OF_WATER:
                return Ocarina && OcarinaAButton && OcarinaCLeftButton && OcarinaCRightButton && OcarinaCDownButton;
            case RG_REQUIEM_OF_SPIRIT:
                return Ocarina && OcarinaAButton && OcarinaCRightButton && OcarinaCDownButton;
            case RG_NOCTURNE_OF_SHADOW:
                return Ocarina && OcarinaAButton && OcarinaCLeftButton && OcarinaCRightButton && OcarinaCDownButton;
            case RG_PRELUDE_OF_LIGHT:
                return Ocarina && OcarinaCLeftButton && OcarinaCRightButton && OcarinaCUpButton;

            // Misc. Items
            case RG_FISHING_POLE:
                return HasItem(RG_CHILD_WALLET); // as long as you have enough rubies

            // Magic items
            default:
                return MagicMeter && (IsMagicItem(itemName) || (IsMagicArrow(itemName) && CanUse(RG_FAIRY_BOW)));
        }
    }

    bool Logic::HasProjectile(HasProjectileAge age) {
        return HasExplosives ||
               (age == HasProjectileAge::Child  && (Slingshot || Boomerang)) ||
               (age == HasProjectileAge::Adult  && (Hookshot  || Bow      )) ||
               (age == HasProjectileAge::Both   && (Slingshot || Boomerang)  && (Hookshot || Bow)) ||
               (age == HasProjectileAge::Either && (Slingshot || Boomerang   ||  Hookshot || Bow));
    }

    bool Logic::HasBossSoul(RandomizerGet itemName) {
        if (!ctx->GetOption(RSK_SHUFFLE_BOSS_SOULS)) {
            return true;
        }
        switch(itemName) {
            case RG_GOHMA_SOUL:
            case RG_KING_DODONGO_SOUL:
            case RG_BARINADE_SOUL:
            case RG_PHANTOM_GANON_SOUL:
            case RG_VOLVAGIA_SOUL:
            case RG_MORPHA_SOUL:
            case RG_BONGO_BONGO_SOUL:
            case RG_TWINROVA_SOUL:
                return HasItem(itemName);
            case RG_GANON_SOUL:
                return ctx->GetOption(RSK_SHUFFLE_BOSS_SOULS).Is(RO_BOSS_SOULS_ON_PLUS_GANON) ? HasItem(RG_GANON_SOUL) : true;
            default:
                break;
        }
    }

    uint8_t GetDifficultyValueFromString(Rando::Option& glitchOption) {
        return 0;
    }

    //todo rewrite glitch section

    bool Logic::CanEquipSwap(RandomizerGet itemName) {
        if (!HasItem(itemName))
            return false;
    
        if (CanDoGlitch(GlitchType::EquipSwapDins) || CanDoGlitch(GlitchType::EquipSwap))
            return true;

        return false;
    }

    bool Logic::CanDoGlitch(GlitchType glitch) {
        // TODO: Uncomment when glitches are implemented
        switch(glitch) {
            case GlitchType::EquipSwapDins:
                return ((IsAdult && HasItem(RG_DINS_FIRE)) || (IsChild && (HasItem(RG_STICKS) || HasItem(RG_DINS_FIRE)))) && false; //GlitchEquipSwapDins;
            case GlitchType::EquipSwap: // todo: add bunny hood to adult item equippable list and child trade item to child item equippable list
                return ((IsAdult && (HasItem(RG_DINS_FIRE) || HasItem(RG_FARORES_WIND) || HasItem(RG_NAYRUS_LOVE))) || (IsChild && (HasItem(RG_STICKS) || 
                    HasItem(RG_FAIRY_SLINGSHOT) || HasItem(RG_BOOMERANG) || HasBottle || Nuts || Ocarina || HasItem(RG_LENS_OF_TRUTH) || HasExplosives ||
                    (MagicBean || MagicBeanPack) || HasItem(RG_DINS_FIRE) || HasItem(RG_FARORES_WIND) || HasItem(RG_NAYRUS_LOVE)))) && false; //GlitchEquipSwap;
        }

        //Shouldn't be reached
        return false;
    }

    bool Logic::CanKillEnemy(std::string enemy) {
        //switch(enemy) {} RANDOTODO implement enemies enum
        if (enemy == "Big Skulltula"){
            return CanUse(RG_FAIRY_BOW) || CanUse(RG_FAIRY_SLINGSHOT) || CanJumpslash || CanUse(RG_MEGATON_HAMMER) || CanUse(RG_HOOKSHOT) || CanUse(RG_DINS_FIRE) || HasExplosives;
        }
        //Shouldn't be reached
        return false;
    }

    bool Logic::CanPassEnemy(std::string enemy) {
        //switch(enemy) {} RANDOTODO implement enemies enum
        if (CanKillEnemy(enemy)){
            return true;
        }
        if (enemy == "Big Skulltula"){
            return Nuts || CanUse(RG_BOOMERANG);
        }
        return false;
    }

    Logic::Logic() {
        
    }

    uint8_t Logic::BottleCount() {
        uint8_t count = 0;
        for (int i = SLOT_BOTTLE_1; i <= SLOT_BOTTLE_4; i++) {
            uint8_t item = ctx->GetSaveContext()->inventory.items[i];
            if (item != ITEM_NONE && (item == ITEM_LETTER_RUTO && DeliverLetter) && item != ITEM_BIG_POE) {
                count++;
            }
        }
        return count;
    }

    // Updates all logic helpers. Should be called whenever a non-helper is changed
    void Logic::UpdateHelpers() {
        OcarinaButtons  =  (HasItem(RG_OCARINA_A_BUTTON) ? 1 : 0) +
                           (HasItem(RG_OCARINA_C_LEFT_BUTTON) ? 1 : 0) +
                           (HasItem(RG_OCARINA_C_RIGHT_BUTTON) ? 1 : 0) +
                           (HasItem(RG_OCARINA_C_UP_BUTTON) ? 1 : 0) +
                           (HasItem(RG_OCARINA_C_DOWN_BUTTON) ? 1 : 0);
        ZeldasLetter  = HasItem(RG_ZELDAS_LETTER);
        WeirdEgg      = CanUse(RG_WEIRD_EGG);
        Bombchus      = HasItem(RG_PROGRESSIVE_BOMBCHUS);
        //Bombchus5     = false;
        //Bombchus10    = false;
        //Bombchus20    = false;
        //MagicBean     = false;
        //MagicBeanPack = false;
        RutosLetter   = CanUse(RG_RUTOS_LETTER);
        Boomerang     = CanUse(RG_BOOMERANG);
        DinsFire      = CanUse(RG_DINS_FIRE);
        FaroresWind   = CanUse(RG_FARORES_WIND);
        NayrusLove    = CanUse(RG_NAYRUS_LOVE);
        LensOfTruth   = CanUse(RG_LENS_OF_TRUTH);
        ShardOfAgony  = HasItem(RG_STONE_OF_AGONY);
        //SkullMask     = false;
        //MaskOfTruth   = false;

        //Adult logic
        Hammer          = CanUse(RG_MEGATON_HAMMER);
        IronBoots       = CanUse(RG_IRON_BOOTS);
        HoverBoots      = CanUse(RG_HOVER_BOOTS);
        MirrorShield    = CanUse(RG_MIRROR_SHIELD);
        GoronTunic      = CanUse(RG_GORON_TUNIC);
        ZoraTunic       = CanUse(RG_ZORA_TUNIC);
        //Epona         = false;
        //BigPoe        = false;
        GerudoToken     = HasItem(RG_GERUDO_MEMBERSHIP_CARD);
        FireArrows      = CanUse(RG_FIRE_ARROWS);
        IceArrows       = CanUse(RG_ICE_ARROWS);
        LightArrows     = CanUse(RG_LIGHT_ARROWS);
        KokiriSword     = CanUse(RG_KOKIRI_SWORD);
        MasterSword     = CanUse(RG_MASTER_SWORD);
        BiggoronSword   = CanUse(RG_MASTER_SWORD);
        NumBottles      = ((NoBottles) ? 0 : BottleCount());
        HasBottle       = NumBottles >= 1;
        Slingshot       = CanUse(RG_FAIRY_SLINGSHOT) && (BuySeed || AmmoCanDrop);
        Ocarina         = HasItem(RG_FAIRY_OCARINA);
        OcarinaOfTime   = HasItem(RG_OCARINA_OF_TIME);
        MagicMeter      = HasItem(RG_MAGIC_SINGLE) && (AmmoCanDrop || (HasBottle && BuyMagicPotion));
        BombBag         = HasItem(RG_BOMB_BAG) && (BuyBomb || AmmoCanDrop);
        Hookshot        = CanUse(RG_HOOKSHOT);
        Longshot        = CanUse(RG_LONGSHOT);
        Bow             = CanUse(RG_FAIRY_BOW) && (BuyArrow || AmmoCanDrop);
        GoronBracelet   = HasItem(RG_GORONS_BRACELET);
        SilverGauntlets = HasItem(RG_SILVER_GAUNTLETS);
        GoldenGauntlets = HasItem(RG_GOLDEN_GAUNTLETS);
        Swim            = HasItem(RG_BRONZE_SCALE);
        SilverScale     = HasItem(RG_SILVER_SCALE);
        GoldScale       = HasItem(RG_GOLDEN_SCALE);
        ChildsWallet    = HasItem(RG_CHILD_WALLET);
        AdultsWallet    = HasItem(RG_ADULT_WALLET);
        BiggoronSword   = HasItem(RG_BIGGORON_SWORD);

        CanSummonGohma        = HasBossSoul(RG_GOHMA_SOUL);
        CanSummonKingDodongo  = HasBossSoul(RG_KING_DODONGO_SOUL);
        CanSummonBarinade     = HasBossSoul(RG_BARINADE_SOUL);
        CanSummonPhantomGanon = HasBossSoul(RG_PHANTOM_GANON_SOUL);
        CanSummonVolvagia     = HasBossSoul(RG_VOLVAGIA_SOUL);
        CanSummonMorpha       = HasBossSoul(RG_MORPHA_SOUL);
        CanSummonBongoBongo   = HasBossSoul(RG_BONGO_BONGO_SOUL);
        CanSummonTwinrova     = HasBossSoul(RG_TWINROVA_SOUL);
        CanSummonGanon        = HasBossSoul(RG_GANON_SOUL);

        // Boss Keys
        BossKeyForestTemple = HasItem(RG_FOREST_TEMPLE_BOSS_KEY);
        BossKeyFireTemple   = HasItem(RG_FIRE_TEMPLE_BOSS_KEY);
        BossKeyWaterTemple  = HasItem(RG_WATER_TEMPLE_BOSS_KEY);
        BossKeySpiritTemple = HasItem(RG_SPIRIT_TEMPLE_BOSS_KEY);
        BossKeyShadowTemple = HasItem(RG_SHADOW_TEMPLE_BOSS_KEY);
        BossKeyGanonsCastle = HasItem(RG_GANONS_CASTLE_BOSS_KEY);

        KokiriEmerald   = HasItem(RG_KOKIRI_EMERALD);
        GoronRuby       = HasItem(RG_GORON_RUBY);
        ZoraSapphire    = HasItem(RG_ZORA_SAPPHIRE);
        ForestMedallion = HasItem(RG_FOREST_MEDALLION);
        FireMedallion   = HasItem(RG_FIRE_MEDALLION);
        WaterMedallion  = HasItem(RG_WATER_MEDALLION);
        SpiritMedallion = HasItem(RG_SPIRIT_MEDALLION);
        ShadowMedallion = HasItem(RG_SHADOW_MEDALLION);
        LightMedallion  = HasItem(RG_LIGHT_MEDALLION);

        //TODO: need flags somewhere for 
        //Eyedrops = Eyedrops || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && ClaimCheck);
        //EyeballFrog = EyeballFrog || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && Eyedrops);
        //Prescription = Prescription || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && EyeballFrog);
        //BrokenSword = BrokenSword || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && Prescription);
        //PoachersSaw = PoachersSaw || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && BrokenSword);
        //OddPoultice = OddPoultice || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && PoachersSaw);
        //OddMushroom = OddMushroom || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && OddPoultice);
        //Cojiro = Cojiro || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && OddMushroom);
        //PocketEgg = PocketEgg || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && Cojiro);

        //BaseHearts + HeartContainer + (PieceOfHeart >> 2); "Hearts"
        //all keys
        DoubleDefense = HasItem(RG_DOUBLE_DEFENSE);
        //TriforcePieces = ;
        //Greg = ;
        //GoldSkulltulaTokens = ;

        //you need at least 2 buttons for scarecrow song
        ScarecrowSong    = ScarecrowSong || (ctx->GetOption(RSK_SKIP_SCARECROWS_SONG) && Ocarina && OcarinaButtons >= 2) || (ChildScarecrow && AdultScarecrow);
        Scarecrow        = Hookshot && ScarecrowSong;
        DistantScarecrow = Longshot && ScarecrowSong;

        //Drop Access
        DekuStickDrop = StickPot || DekuBabaSticks;
        DekuNutDrop   = (NutPot  || NutCrate         || DekuBabaNuts) && AmmoCanDrop;
        BugsAccess    = BugShrub || WanderingBugs    || BugRock;
        FishAccess    = LoneFish || FishGroup;
        FairyAccess   = FairyPot || GossipStoneFairy || BeanPlantFairy || ButterflyFairy || FreeFairies || FairyPond;


        //refills
        Bombs        = BombBag;
        Nuts         = DekuNutDrop || Nuts;
        Sticks       = DekuStickDrop || Sticks;
        Bugs         = HasBottle && BugsAccess;
        BlueFire     = (HasBottle && BlueFireAccess) || (ctx->GetOption(RSK_BLUE_FIRE_ARROWS) && CanUse(RG_ICE_ARROWS));
        Fish         = HasBottle && FishAccess;
        Fairy        = HasBottle && FairyAccess;

        FoundBombchus   = (BombchuDrop || Bombchus || Bombchus5 || Bombchus10 || Bombchus20) && (BombBag || ctx->GetOption(RSK_BOMBCHUS_IN_LOGIC));
        CanPlayBowling  = ChildsWallet && ((ctx->GetOption(RSK_BOMBCHUS_IN_LOGIC) && FoundBombchus) || (!ctx->GetOption(RSK_BOMBCHUS_IN_LOGIC) && BombBag));
        // TODO: Implement Ammo Drop Setting in place of bombchu drops
        HasBombchus = (BuyBombchus || (ctx->GetOption(RSK_ENABLE_BOMBCHU_DROPS).Is(RO_AMMO_DROPS_ON/*_PLUS_BOMBCHU*/) && FoundBombchus));

        HasExplosives =  Bombs || (ctx->GetOption(RSK_BOMBCHUS_IN_LOGIC) && HasBombchus);

        HasBoots = IronBoots || HoverBoots;

        //Unshuffled adult trade quest
        Eyedrops     = Eyedrops     || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && ClaimCheck);
        EyeballFrog  = EyeballFrog  || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && Eyedrops);
        Prescription = Prescription || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && EyeballFrog);
        BrokenSword  = BrokenSword  || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && Prescription);
        PoachersSaw  = PoachersSaw  || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && BrokenSword);
        OddPoultice  = OddPoultice  || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && PoachersSaw);
        OddMushroom  = OddMushroom  || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && OddPoultice);
        Cojiro       = Cojiro       || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && OddMushroom);
        PocketEgg    = PocketEgg    || (!ctx->GetOption(RSK_SHUFFLE_ADULT_TRADE) && Cojiro);

        // IsChild = Age == AGE_CHILD;
        // IsAdult = Age == AGE_ADULT;

        CanBlastOrSmash = HasExplosives || CanUse(RG_MEGATON_HAMMER);
        CanChildAttack  = IsChild && (Slingshot || Boomerang || Sticks || KokiriSword || HasExplosives || CanUse(RG_DINS_FIRE) || CanUse(RG_MASTER_SWORD) || CanUse(RG_MEGATON_HAMMER) || CanUse(RG_BIGGORON_SWORD));
        CanChildDamage  = IsChild && (Slingshot ||              Sticks || KokiriSword || HasExplosives || CanUse(RG_DINS_FIRE) || CanUse(RG_MASTER_SWORD) || CanUse(RG_MEGATON_HAMMER) || CanUse(RG_BIGGORON_SWORD));
        CanAdultAttack  = IsAdult && (CanUse(RG_FAIRY_BOW) || CanUse(RG_BOOMERANG)       || CanUse(RG_STICKS) || CanUse(RG_KOKIRI_SWORD) || HasExplosives || CanUse(RG_DINS_FIRE) || MasterSword || Hammer || BiggoronSword || Hookshot);
        CanAdultDamage  = IsAdult && (CanUse(RG_FAIRY_BOW) || CanUse(RG_STICKS)          || CanUse(RG_KOKIRI_SWORD) || HasExplosives || CanUse(RG_DINS_FIRE) || MasterSword || Hammer || BiggoronSword);
        CanStunDeku     = CanAdultAttack || CanChildAttack || Nuts || HasShield;
        CanCutShrubs    = CanUse(RG_KOKIRI_SWORD) || CanUse(RG_BOOMERANG) || HasExplosives || CanUse(RG_MASTER_SWORD) || CanUse(RG_MEGATON_HAMMER) || CanUse(RG_BIGGORON_SWORD);
        CanDive         = ProgressiveScale >= 2;
        CanLeaveForest  = ctx->GetOption(RSK_FOREST).IsNot(RO_FOREST_CLOSED) || IsAdult || DekuTreeClear || ctx->GetOption(RSK_SHUFFLE_INTERIOR_ENTRANCES) || ctx->GetOption(RSK_SHUFFLE_OVERWORLD_ENTRANCES);
        CanPlantBugs    = IsChild && Bugs;
        CanRideEpona    = IsAdult && Epona && CanUse(RG_EPONAS_SONG);
        CanSummonGossipFairyWithoutSuns = CanUse(RG_ZELDAS_LULLABY) || CanUse(RG_EPONAS_SONG) || CanUse(RG_SONG_OF_TIME);
        CanSummonGossipFairy            = CanSummonGossipFairyWithoutSuns || CanUse(RG_SUNS_SONG);
        Hearts          = BaseHearts + HeartContainer + (PieceOfHeart >> 2);
        EffectiveHealth = ((Hearts << (2 + DoubleDefense)) >> Multiplier) + ((Hearts << (2 + DoubleDefense)) % (1 << Multiplier) > 0); //Number of half heart hits to die, ranges from 1 to 160
        FireTimer       = CanUse(RG_GORON_TUNIC) ? 255 : (ctx->GetTrickOption(RT_FEWER_TUNIC_REQUIREMENTS)) ? (Hearts * 8) : 0;
        WaterTimer      = CanUse(RG_ZORA_TUNIC) ? 255 : (ctx->GetTrickOption(RT_FEWER_TUNIC_REQUIREMENTS)) ? (Hearts * 8) : 0;
        NeedNayrusLove      = (EffectiveHealth == 1);
        CanSurviveDamage    = !NeedNayrusLove || CanUse(RG_NAYRUS_LOVE);
        CanTakeDamage       = Fairy || CanSurviveDamage;
        CanTakeDamageTwice  = (Fairy && NumBottles >= 2) || ((EffectiveHealth == 2) && (CanUse(RG_NAYRUS_LOVE) || Fairy)) || (EffectiveHealth > 2);
        //CanPlantBean        = IsChild && (MagicBean || MagicBeanPack);
        CanOpenBombGrotto   = CanBlastOrSmash       && (ShardOfAgony || ctx->GetTrickOption(RT_GROTTOS_WITHOUT_AGONY));
        CanOpenStormGrotto  = CanUse(RG_SONG_OF_STORMS) && (ShardOfAgony || ctx->GetTrickOption(RT_GROTTOS_WITHOUT_AGONY));
        HookshotOrBoomerang = CanUse(RG_HOOKSHOT) || CanUse(RG_BOOMERANG);
        CanGetNightTimeGS   = (CanUse(RG_SUNS_SONG) || !ctx->GetOption(RSK_SKULLS_SUNS_SONG));
        CanBreakUpperBeehives = HookshotOrBoomerang || (ctx->GetTrickOption(RT_BOMBCHU_BEEHIVES) && HasBombchus);
        CanBreakLowerBeehives = CanBreakUpperBeehives || Bombs;
        CanFish = ChildsWallet && (CanUse(RG_FISHING_POLE) || !ctx->GetOption(RSK_SHUFFLE_FISHING_POLE));
        CanGetChildFish = CanFish && (IsChild || (IsAdult && !ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT)));
        CanGetAdultFish = CanFish && IsAdult && ctx->GetOption(RSK_FISHSANITY_AGE_SPLIT);

        GuaranteeTradePath     = ctx->GetOption(RSK_SHUFFLE_INTERIOR_ENTRANCES) || ctx->GetOption(RSK_SHUFFLE_OVERWORLD_ENTRANCES) || ctx->GetTrickOption(RT_DMT_BOLERO_BIGGORON) || CanBlastOrSmash || StopGCRollingGoronAsAdult;
        //GuaranteeHint          = (hints == "Mask" && MaskofTruth) || (hints == "Agony") || (hints != "Mask" && hints != "Agony");
        HasFireSource          = CanUse(RG_DINS_FIRE) || CanUse(RG_FIRE_ARROWS);
        HasFireSourceWithTorch = HasFireSource || CanUse(RG_STICKS);

        //Gerudo Fortress
        CanFinishGerudoFortress = (ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_NORMAL)    && GerudoFortressKeys >= 4 && (CanUse(RG_KOKIRI_SWORD) || CanUse(RG_MASTER_SWORD) || CanUse(RG_BIGGORON_SWORD)) && (GerudoToken || CanUse(RG_FAIRY_BOW) || CanUse(RG_HOOKSHOT) || CanUse(RG_HOVER_BOOTS) || ctx->GetTrickOption(RT_GF_KITCHEN))) ||
                                    (ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_FAST)      && GerudoFortressKeys >= 1 && (CanUse(RG_KOKIRI_SWORD) || CanUse(RG_MASTER_SWORD) || CanUse(RG_BIGGORON_SWORD))) ||
                                    (ctx->GetOption(RSK_GERUDO_FORTRESS).IsNot(RO_GF_NORMAL) && ctx->GetOption(RSK_GERUDO_FORTRESS).IsNot(RO_GF_FAST));

        HasShield          = CanUse(RG_HYLIAN_SHIELD) || CanUse(RG_DEKU_SHIELD); //Mirror shield can't reflect attacks
        CanShield          = CanUse(RG_MIRROR_SHIELD) || HasShield;
        ChildShield        = IsChild && CanUse(RG_DEKU_SHIELD); //hylian shield is not helpful for child
        AdultReflectShield = IsAdult && CanUse(RG_HYLIAN_SHIELD); //Mirror shield can't reflect attacks
        AdultShield        = IsAdult && (CanUse(RG_HYLIAN_SHIELD) || CanUse(RG_MIRROR_SHIELD));
        CanShieldFlick     = ChildShield || AdultShield;
        CanJumpslash       = CanUse(RG_STICKS) || CanUse(RG_KOKIRI_SWORD) || CanUse(RG_MASTER_SWORD) || CanUse(RG_BIGGORON_SWORD); // Not including hammer as hammer jump attacks can be weird
        CanUseProjectile   = HasExplosives || CanUse(RG_FAIRY_BOW) || CanUse(RG_HOOKSHOT) || CanUse(RG_FAIRY_SLINGSHOT) || CanUse(RG_BOOMERANG);
        CanUseMagicArrow   = CanUse(RG_FIRE_ARROWS) || CanUse(RG_ICE_ARROWS) || CanUse(RG_LIGHT_ARROWS);

        //Bridge and LACS Requirements
        MedallionCount        = (ForestMedallion ? 1:0) + (FireMedallion ? 1:0) + (WaterMedallion ? 1:0) + (SpiritMedallion ? 1:0) + (ShadowMedallion ? 1:0) + (LightMedallion ? 1:0);
        StoneCount            = (KokiriEmerald ? 1:0) + (GoronRuby ? 1:0) + (ZoraSapphire ? 1:0);
        DungeonCount          = (DekuTreeClear ? 1:0) + (DodongosCavernClear ? 1:0) + (JabuJabusBellyClear ? 1:0) + (ForestTempleClear ? 1:0) + (FireTempleClear ? 1:0) + (WaterTempleClear ? 1:0) + (SpiritTempleClear ? 1:0) + (ShadowTempleClear ? 1:0);
        HasAllStones          = StoneCount == 3;
        HasAllMedallions      = MedallionCount == 6;
        GregInBridgeLogic     = ctx->GetOption(RSK_BRIDGE_OPTIONS).Is(RO_BRIDGE_GREG);
        GregInLacsLogic       = ctx->GetOption(RSK_LACS_OPTIONS).Is(RO_LACS_GREG_REWARD);

        CanBuildRainbowBridge = ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_ALWAYS_OPEN)                                                                         ||
                                (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_VANILLA)    && ShadowMedallion && SpiritMedallion && LightArrows)             ||
                                (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_STONES)     && StoneCount + (Greg && GregInBridgeLogic ? 1 : 0) >= ctx->GetOption(RSK_RAINBOW_BRIDGE_STONE_COUNT).Value<uint8_t>())                    ||
                                (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_MEDALLIONS) && MedallionCount + (Greg && GregInBridgeLogic ? 1 : 0) >= ctx->GetOption(RSK_RAINBOW_BRIDGE_MEDALLION_COUNT).Value<uint8_t>())            ||
                                (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_DUNGEON_REWARDS)    && StoneCount + MedallionCount + (Greg && GregInBridgeLogic ? 1 : 0) >= ctx->GetOption(RSK_RAINBOW_BRIDGE_REWARD_COUNT).Value<uint8_t>())  ||
                                (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_DUNGEONS)   && DungeonCount + (Greg && GregInBridgeLogic ? 1 : 0) >= ctx->GetOption(RSK_RAINBOW_BRIDGE_DUNGEON_COUNT).Value<uint8_t>())                ||
                                (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_TOKENS)     && GoldSkulltulaTokens >= ctx->GetOption(RSK_RAINBOW_BRIDGE_TOKEN_COUNT).Value<uint8_t>()) ||
                                (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_GREG)       && Greg);

        CanTriggerLACS = (ctx->GetSettings()->LACSCondition() == RO_LACS_VANILLA    && ShadowMedallion && SpiritMedallion)                          ||
                            (ctx->GetSettings()->LACSCondition() == RO_LACS_STONES     && StoneCount + (Greg && GregInLacsLogic ? 1 : 0) >= ctx->GetOption(RSK_LACS_STONE_COUNT).Value<uint8_t>())                    ||
                            (ctx->GetSettings()->LACSCondition() == RO_LACS_MEDALLIONS && MedallionCount + (Greg && GregInLacsLogic ? 1 : 0) >= ctx->GetOption(RSK_LACS_MEDALLION_COUNT).Value<uint8_t>())            ||
                            (ctx->GetSettings()->LACSCondition() == RO_LACS_REWARDS    && StoneCount + MedallionCount + (Greg && GregInLacsLogic ? 1 : 0) >= ctx->GetOption(RSK_LACS_REWARD_COUNT).Value<uint8_t>())  ||
                            (ctx->GetSettings()->LACSCondition() == RO_LACS_DUNGEONS   && DungeonCount + (Greg && GregInLacsLogic ? 1 : 0) >= ctx->GetOption(RSK_LACS_DUNGEON_COUNT).Value<uint8_t>())                ||
                            (ctx->GetSettings()->LACSCondition() == RO_LACS_TOKENS     && GoldSkulltulaTokens >= ctx->GetOption(RSK_LACS_TOKEN_COUNT).Value<uint8_t>());
        CanCompleteTriforce = TriforcePieces >= ctx->GetOption(RSK_TRIFORCE_HUNT_PIECES_REQUIRED).Value<uint8_t>();
    }

    bool Logic::SmallKeys(RandomizerRegion dungeon, uint8_t requiredAmount) {
        return SmallKeys(dungeon, requiredAmount, requiredAmount);
    }

    bool Logic::SmallKeys(RandomizerRegion dungeon, uint8_t requiredAmountGlitchless, uint8_t requiredAmountGlitched) {
        switch (dungeon) {
            case RR_FOREST_TEMPLE:
                /*if (IsGlitched && (GetDifficultyValueFromString(GlitchHookshotJump_Boots) >= static_cast<uint8_t>(GlitchDifficulty::INTERMEDIATE) || GetDifficultyValueFromString(GlitchHoverBoost) >= static_cast<uint8_t>(GlitchDifficulty::NOVICE) ||
                                    (GetDifficultyValueFromString(GlitchHover) >= static_cast<uint8_t>(GlitchDifficulty::NOVICE) && GetDifficultyValueFromString(GlitchISG) >= static_cast<uint8_t>(GlitchDifficulty::INTERMEDIATE)))) {
                    return ForestTempleKeys >= requiredAmountGlitched;
                }*/
                {
                    auto smallKeys = ctx->GetSmallKeyCount(SCENE_FOREST_TEMPLE);
                    if (ForestTempleKeys != smallKeys)
                        SPDLOG_ERROR("Forest temple small key count mismatch: logicVar {}, saveContext {}", ForestTempleKeys, smallKeys);
                }
                return ForestTempleKeys >= requiredAmountGlitchless;

            case RR_FIRE_TEMPLE:
                /*if (IsGlitched && (GetDifficultyValueFromString(GlitchLedgeClip) >= static_cast<uint8_t>(GlitchDifficulty::INTERMEDIATE) || GetDifficultyValueFromString(GlitchHover) >= static_cast<uint8_t>(GlitchDifficulty::INTERMEDIATE))) {
                    return FireTempleKeys >= requiredAmountGlitched;
                }*/
                {
                    auto smallKeys = ctx->GetSmallKeyCount(SCENE_FIRE_TEMPLE);
                    if (FireTempleKeys != smallKeys)
                        SPDLOG_ERROR("Fire temple small key count mismatch: logicVar {}, saveContext {}", FireTempleKeys, smallKeys);
                }
                return FireTempleKeys >= requiredAmountGlitchless;

            case RR_WATER_TEMPLE:
                /*if (IsGlitched && (false)) {
                    return WaterTempleKeys >= requiredAmountGlitched;
                }*/
                {
                    auto smallKeys = ctx->GetSmallKeyCount(SCENE_WATER_TEMPLE);
                    if (WaterTempleKeys != smallKeys)
                        SPDLOG_ERROR("Water temple small key count mismatch: logicVar {}, saveContext {}", WaterTempleKeys, smallKeys);
                }
                return WaterTempleKeys >= requiredAmountGlitchless;

            case RR_SPIRIT_TEMPLE:
                /*if (IsGlitched && (false)) {
                    return SpiritTempleKeys >= requiredAmountGlitched;
                }*/
                {
                    auto smallKeys = ctx->GetSmallKeyCount(SCENE_SPIRIT_TEMPLE);
                    if (SpiritTempleKeys != smallKeys)
                        SPDLOG_ERROR("Spirit temple small key count mismatch: logicVar {}, saveContext {}", SpiritTempleKeys, smallKeys);
                }
                return SpiritTempleKeys >= requiredAmountGlitchless;

            case RR_SHADOW_TEMPLE:
                /*if (IsGlitched && (GetDifficultyValueFromString(GlitchHookshotClip) >= static_cast<uint8_t>(GlitchDifficulty::NOVICE))) {
                    return ShadowTempleKeys >= requiredAmountGlitched;
                }*/
                {
                    auto smallKeys = ctx->GetSmallKeyCount(SCENE_SHADOW_TEMPLE);
                    if (ShadowTempleKeys != smallKeys)
                        SPDLOG_ERROR("Shadow temple small key count mismatch: logicVar {}, saveContext {}", ShadowTempleKeys, smallKeys);
                }
                return ShadowTempleKeys >= requiredAmountGlitchless;

            case RR_BOTTOM_OF_THE_WELL:
                /*if (IsGlitched && (false)) {
                    return BottomOfTheWellKeys >= requiredAmountGlitched;
                }*/
                {
                    auto smallKeys = ctx->GetSmallKeyCount(SCENE_BOTTOM_OF_THE_WELL);
                    if (BottomOfTheWellKeys != smallKeys)
                        SPDLOG_ERROR("BotW temple small key count mismatch: logicVar {}, saveContext {}", BottomOfTheWellKeys, smallKeys);
                }
                return BottomOfTheWellKeys >= requiredAmountGlitchless;

            case RR_GERUDO_TRAINING_GROUNDS:
                /*if (IsGlitched && (false)) {
                    return GerudoTrainingGroundsKeys >= requiredAmountGlitched;
                }*/
                {
                    auto smallKeys = ctx->GetSmallKeyCount(SCENE_GERUDO_TRAINING_GROUND);
                    if (GerudoTrainingGroundsKeys != smallKeys)
                        SPDLOG_ERROR("GTG small key count mismatch: logicVar {}, saveContext {}", GerudoTrainingGroundsKeys, smallKeys);
                }
                return GerudoTrainingGroundsKeys >= requiredAmountGlitchless;

            case RR_GANONS_CASTLE:
                /*if (IsGlitched && (false)) {
                    return GanonsCastleKeys >= requiredAmountGlitched;
                }*/
                {
                    auto smallKeys = ctx->GetSmallKeyCount(SCENE_INSIDE_GANONS_CASTLE);
                    if (GanonsCastleKeys != smallKeys)
                        SPDLOG_ERROR("Ganon's Castle small key count mismatch: logicVar {}, saveContext {}", GanonsCastleKeys, smallKeys);
                }
                return GanonsCastleKeys >= requiredAmountGlitchless;

            case RR_MARKET_TREASURE_CHEST_GAME:
                /*if (IsGlitched && (false)) {
                    return TreasureGameKeys >= requiredAmountGlitched;
                }*/
                return TreasureGameKeys >= requiredAmountGlitchless;

            default:
                return false;
        }
    }

    bool Logic::EventsUpdated() {
        if (DekuTreeClearPast        != DekuTreeClear        ||
            GoronRubyPast            != GoronRuby            ||
            ZoraSapphirePast         != ZoraSapphire         ||
            ForestTrialClearPast     != ForestTrialClear     ||
            FireTrialClearPast       != FireTrialClear       ||
            WaterTrialClearPast      != WaterTrialClear      ||
            ShadowTrialClearPast     != ShadowTrialClear     ||
            SpiritTrialClearPast     != SpiritTrialClear     ||
            LightTrialClearPast      != LightTrialClear      ||
            DrainWellPast            != DrainWell            ||
            DampesWindmillAccessPast != DampesWindmillAccess ||
            TimeTravelPast           != TimeTravel) {
            DekuTreeClearPast         = DekuTreeClear;
            GoronRubyPast             = GoronRuby;
            ZoraSapphirePast          = ZoraSapphire;
            ForestTrialClearPast      = ForestTrialClear;
            FireTrialClearPast        = FireTrialClear;
            WaterTrialClearPast       = WaterTrialClear;
            ShadowTrialClearPast      = ShadowTrialClear;
            SpiritTrialClearPast      = SpiritTrialClear;
            LightTrialClearPast       = LightTrialClear;
            DrainWellPast             = DrainWell;
            DampesWindmillAccessPast  = DampesWindmillAccess;
            return true;
        }
        return false;
    }

    void Logic::SetContext(std::shared_ptr<Context> _ctx) {
        ctx = _ctx;
    }

    void Logic::Reset() {
        //SPDLOG_INFO("Logic reset.");
        ctx->NewSaveContext();
        //Settings-dependent variables
        IsKeysanity = ctx->GetOption(RSK_KEYSANITY).Is(RO_DUNGEON_ITEM_LOC_ANYWHERE) || 
                    ctx->GetOption(RSK_KEYSANITY).Is(RO_DUNGEON_ITEM_LOC_ANYWHERE) || 
                    ctx->GetOption(RSK_KEYSANITY).Is(RO_DUNGEON_ITEM_LOC_ANYWHERE);
        AmmoCanDrop = /*AmmoDrops.IsNot(AMMODROPS_NONE) TODO: AmmoDrop setting*/ true;

        //Child item logic
        KokiriSword   = false;
        ZeldasLetter  = false;
        WeirdEgg      = false;
        HasBottle     = false;
        Bombchus      = false;
        Bombchus5     = false;
        Bombchus10    = false;
        Bombchus20    = false;
        MagicBean     = false;
        MagicBeanPack = false;
        RutosLetter   = false;
        Boomerang     = false;
        DinsFire      = false;
        FaroresWind   = false;
        NayrusLove    = false;
        LensOfTruth   = false;
        ShardOfAgony  = false;
        SkullMask     = false;
        MaskOfTruth   = false;

        //Adult logic
        Hammer        = false;
        IronBoots     = false;
        HoverBoots    = false;
        MirrorShield  = false;
        GoronTunic    = false;
        ZoraTunic     = false;
        Epona         = false;
        //BigPoe        = false;
        GerudoToken   = false;
        FireArrows    = false;
        IceArrows     = false;
        LightArrows   = false;
        MasterSword   = false;
        BiggoronSword = false;

        //Trade Quest
        PocketEgg     = false;
        Cojiro        = false;
        OddMushroom   = false;
        OddPoultice   = false;
        PoachersSaw   = false;
        BrokenSword   = false;
        Prescription  = false;
        EyeballFrog   = false;
        Eyedrops      = false;
        ClaimCheck    = false;

        //Trade Quest Events
        WakeUpAdultTalon   = false;
        CojiroAccess       = false;
        OddMushroomAccess  = false;
        OddPoulticeAccess  = false;
        PoachersSawAccess  = false;
        BrokenSwordAccess  = false;
        PrescriptionAccess = false;
        EyeballFrogAccess  = false;
        EyedropsAccess     = false;
        DisableTradeRevert = false;

        //Songs
        ZeldasLullaby    = false;
        SariasSong       = false;
        SunsSong         = false;
        SongOfStorms     = false;
        EponasSong       = false;
        SongOfTime       = false;
        MinuetOfForest   = false;
        BoleroOfFire     = false;
        SerenadeOfWater  = false;
        RequiemOfSpirit  = false;
        NocturneOfShadow = false;
        PreludeOfLight   = false;

        //Stones and Meddallions
        ForestMedallion = false;
        FireMedallion   = false;
        WaterMedallion  = false;
        SpiritMedallion = false;
        ShadowMedallion = false;
        LightMedallion  = false;
        KokiriEmerald   = false;
        GoronRuby       = false;
        ZoraSapphire    = false;

        //Dungeon Clears
        DekuTreeClear       = false;
        DodongosCavernClear = false;
        JabuJabusBellyClear = false;
        ForestTempleClear   = false;
        FireTempleClear     = false;
        WaterTempleClear    = false;
        SpiritTempleClear   = false;
        ShadowTempleClear   = false;

        //Trial Clears
        ForestTrialClear = false;
        FireTrialClear   = false;
        WaterTrialClear  = false;
        SpiritTrialClear = false;
        ShadowTrialClear = false;
        LightTrialClear  = false;

        //Greg
        Greg = false;
        GregInBridgeLogic = false;
        GregInLacsLogic = false;

        //Ocarina C Buttons
        bool ocBtnShuffle = ctx->GetOption(RSK_SHUFFLE_OCARINA_BUTTONS).Is(true);
        OcarinaAButton = !ocBtnShuffle;
        OcarinaCLeftButton = !ocBtnShuffle;
        OcarinaCRightButton = !ocBtnShuffle;
        OcarinaCUpButton = !ocBtnShuffle;
        OcarinaCDownButton = !ocBtnShuffle;
        ctx->SetRandoInf(RAND_INF_HAS_OCARINA_A, ocBtnShuffle);
        ctx->SetRandoInf(RAND_INF_HAS_OCARINA_C_UP, ocBtnShuffle);
        ctx->SetRandoInf(RAND_INF_HAS_OCARINA_C_DOWN, ocBtnShuffle);
        ctx->SetRandoInf(RAND_INF_HAS_OCARINA_C_LEFT, ocBtnShuffle);
        ctx->SetRandoInf(RAND_INF_HAS_OCARINA_C_RIGHT, ocBtnShuffle);

        //Progressive Items
        ProgressiveBulletBag  = 0;
        ProgressiveBombBag    = 0;
        ProgressiveMagic      = 0;
        //If we're not shuffling swim, we start with it (scale 1)
        ProgressiveScale      = ctx->GetOption(RSK_SHUFFLE_SWIM).Is(true) ? 0 : 1;
        ctx->SetUpgrade(UPG_SCALE, ProgressiveScale);
        ProgressiveHookshot   = 0;
        ProgressiveBow        = 0;
        //If we're not shuffling child's wallet, we start with it (wallet 1)
        ProgressiveWallet     = ctx->GetOption(RSK_SHUFFLE_CHILD_WALLET).Is(true) ? 0 : 1;
        ctx->SetUpgrade(UPG_WALLET, ProgressiveWallet);
        ProgressiveStrength   = 0;
        ProgressiveOcarina    = 0;
        ProgressiveGiantKnife = 0;

        //Keys
        ForestTempleKeys          = 0;
        //If not keysanity, start with 1 logical key to account for automatically unlocking the basement door in vanilla FiT
        FireTempleKeys            = IsKeysanity || ctx->GetDungeon(Rando::FIRE_TEMPLE)->IsMQ() ? 0 : 1;
        ctx->SetSmallKeyCount(SCENE_FIRE_TEMPLE, FireTempleKeys);
        WaterTempleKeys           = 0;
        SpiritTempleKeys          = 0;
        ShadowTempleKeys          = 0;
        GanonsCastleKeys          = 0;
        GerudoFortressKeys        = 0;
        GerudoTrainingGroundsKeys = 0;
        BottomOfTheWellKeys       = 0;
        TreasureGameKeys          = 0;

        //Boss Keys
        BossKeyForestTemple = 0;
        BossKeyFireTemple   = 0;
        BossKeyWaterTemple  = 0;
        BossKeySpiritTemple = 0;
        BossKeyShadowTemple = 0;
        BossKeyGanonsCastle = 0;

        //Gold Skulltula Count
        GoldSkulltulaTokens = 0;

        //Bottle Count
        Bottles    = 0;
        NumBottles = 0;
        NoBottles  = false;

        //Triforce Pieces
        TriforcePieces = 0;

        //Boss Souls
        CanSummonGohma        = false;
        CanSummonKingDodongo  = false;
        CanSummonBarinade     = false;
        CanSummonPhantomGanon = false;
        CanSummonVolvagia     = false;
        CanSummonMorpha       = false;
        CanSummonBongoBongo   = false;
        CanSummonTwinrova     = false;
        CanSummonGanon        = false;

        //Drops and Bottle Contents Access
        DekuNutDrop      = false;
        NutPot           = false;
        NutCrate         = false;
        DekuBabaNuts     = false;
        DekuStickDrop    = false;
        StickPot         = false;
        DekuBabaSticks   = false;
        BugsAccess       = false;
        BugShrub         = false;
        WanderingBugs    = false;
        BugRock          = false;
        BlueFireAccess   = false;
        FishAccess       = false;
        FishGroup        = false;
        LoneFish         = false;
        FairyAccess      = false;
        GossipStoneFairy = false;
        BeanPlantFairy   = false;
        ButterflyFairy   = false;
        FairyPot         = false;
        FreeFairies      = false;
        FairyPond        = false;
        BombchuDrop      = false;

        BuyBombchus      = false;
        BuySeed          = false;
        BuyArrow         = false;
        BuyBomb          = false;
        BuyMagicPotion        = false;
        MagicRefill      = false;

        PieceOfHeart     = 0;
        HeartContainer   = 0;
        DoubleDefense    = false;

        /* --- HELPERS, EVENTS, AND LOCATION ACCESS --- */
        /* These are used to simplify reading the logic, but need to be updated
        /  every time a base value is updated.                       */

        Slingshot        = false;
        Ocarina          = false;
        OcarinaOfTime    = false;
        BombBag          = false;
        MagicMeter       = false;
        Hookshot         = false;
        Longshot         = false;
        Bow              = false;
        GoronBracelet    = false;
        SilverGauntlets  = false;
        GoldenGauntlets  = false;
        Swim             = false;
        SilverScale      = false;
        GoldScale        = false;
        ChildsWallet     = false;
        AdultsWallet     = false;

        ChildScarecrow   = false;
        AdultScarecrow   = false;
        ScarecrowSong    = false;
        Scarecrow        = false;
        DistantScarecrow = false;

        Bombs            = false;
        DekuShield       = false;
        HylianShield     = false;
        Nuts             = false;
        Sticks           = false;
        Bugs             = false;
        BlueFire         = false;
        Fish             = false;
        Fairy            = false;
        BottleWithBigPoe = false;

        FoundBombchus    = false;
        CanPlayBowling   = false;
        HasBombchus      = false;
        HasExplosives    = false;
        HasBoots         = false;
        IsChild          = false;
        IsAdult          = false;
        IsGlitched       = ctx->GetOption(RSK_LOGIC_RULES).Is(RO_LOGIC_GLITCHED);
        CanBlastOrSmash  = false;
        CanChildAttack   = false;
        CanChildDamage   = false;
        CanCutShrubs     = false;
        CanDive          = false;
        CanLeaveForest   = false;
        CanPlantBugs     = false;
        CanRideEpona     = false;
        CanStunDeku      = false;
        CanSummonGossipFairy = false;
        CanSummonGossipFairyWithoutSuns = false;
        //CanPlantBean        = false;
        CanOpenBombGrotto     = false;
        CanOpenStormGrotto    = false;
        BigPoeKill            = false;
        HookshotOrBoomerang   = false;
        CanBreakUpperBeehives = false;
        CanBreakLowerBeehives = false;
        CanGetChildFish       = false;
        CanGetAdultFish       = false;
        FishingPole           = false;
        CanFish               = false;

        BaseHearts      = ctx->GetOption(RSK_STARTING_HEARTS).Value<uint8_t>() + 1;
        Hearts          = 0;
        Multiplier      = (ctx->GetOption(RSK_DAMAGE_MULTIPLIER).Value<uint8_t>() < 6) ? ctx->GetOption(RSK_DAMAGE_MULTIPLIER).Value<uint8_t>() : 10;
        EffectiveHealth = 0;
        FireTimer       = 0;
        WaterTimer      = 0;

        GuaranteeTradePath     = false;
        GuaranteeHint          = false;
        HasFireSource          = false;
        HasFireSourceWithTorch = false;

        CanFinishGerudoFortress = false;

        HasShield          = false;
        CanShield          = false;
        ChildShield        = false;
        AdultReflectShield = false;
        AdultShield        = false;
        CanShieldFlick     = false;
        CanJumpslash       = false;
        CanUseProjectile   = false;
        CanUseMagicArrow   = false;

        //Bridge Requirements
        HasAllStones          = false;
        HasAllMedallions      = false;
        CanBuildRainbowBridge = false;
        BuiltRainbowBridge    = false;
        CanTriggerLACS        = false;

        //Other
        AtDay         = false;
        AtNight       = false;
        Age           = ctx->GetSettings()->ResolvedStartingAge();
        ctx->GetSaveContext()->linkAge = !Age;

        //Events
        ShowedMidoSwordAndShield  = false;
        CarpenterRescue           = false;
        GF_GateOpen               = false;
        GtG_GateOpen              = false;
        DampesWindmillAccess      = false;
        DrainWell                 = false;
        GoronCityChildFire        = false;
        GCWoodsWarpOpen           = false;
        GCDaruniasDoorOpenChild   = false;
        StopGCRollingGoronAsAdult = false;
        WaterTempleLow            = false;
        WaterTempleMiddle         = false;
        WaterTempleHigh           = false;
        KakarikoVillageGateOpen   = false;
        KingZoraThawed            = false;
        ForestTempleJoelle        = false;
        ForestTempleBeth          = false;
        ForestTempleJoAndBeth     = false;
        ForestTempleAmy           = false;
        ForestTempleMeg           = false;
        ForestTempleAmyAndMeg     = false;
        FireLoopSwitch            = false;
        LinksCow                  = false;
        AtDampeTime               = false;
        DeliverLetter             = false;
        TimeTravel                = false;

        DrainWellPast            = false;
        DampesWindmillAccessPast = false;
        DekuTreeClearPast        = false;
        GoronRubyPast            = false;
        ZoraSapphirePast         = false;
        ForestTrialClearPast     = false;
        FireTrialClearPast       = false;
        WaterTrialClearPast      = false;
        SpiritTrialClearPast     = false;
        ShadowTrialClearPast     = false;
        LightTrialClearPast      = false;
        BuyDekuShieldPast        = false;
        TimeTravelPast           = false;
    }
}
