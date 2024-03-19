#include "logic.h"

#include <algorithm>
#include <cstdio>
#include <string>
#include <string_view>
#include <vector>

#include "dungeon.h"
#include "context.h"

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

    bool Logic::HasItem(RandomizerGet itemName) {
        auto ctx = Rando::Context::GetInstance();
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
                (itemName == RG_SILVER_GAUNTLETS       && ctx->CurrentUpgrade(UPG_STRENGTH) >= 2) || 
                (itemName == RG_GOLDEN_GAUNTLETS       && ctx->CurrentUpgrade(UPG_STRENGTH) == 3)     ||
                (itemName == RG_GORON_TUNIC            && ctx->CheckEquipment(EQUIP_FLAG_TUNIC_GORON))          ||
                (itemName == RG_ZORA_TUNIC             && ctx->CheckEquipment(EQUIP_FLAG_TUNIC_ZORA))           ||
                (itemName == RG_SCARECROW              && Scarecrow())           ||
                (itemName == RG_DISTANT_SCARECROW      && DistantScarecrow())    ||
                (itemName == RG_HYLIAN_SHIELD          && ctx->CheckEquipment(EQUIP_FLAG_SHIELD_HYLIAN))        ||
                (itemName == RG_MIRROR_SHIELD          && ctx->CheckEquipment(EQUIP_FLAG_SHIELD_MIRROR))        ||
                (itemName == RG_MASTER_SWORD           && ctx->CheckEquipment(EQUIP_FLAG_SWORD_MASTER))         ||
                (itemName == RG_BIGGORON_SWORD         && ctx->CheckEquipment(EQUIP_FLAG_SWORD_BGS) && ctx->GetSaveContext()->bgsFlag)       ||
                (itemName == RG_FAIRY_SLINGSHOT        && ctx->CheckInventory(ITEM_SLINGSHOT, true))           ||
                (itemName == RG_BOOMERANG              && ctx->CheckInventory(ITEM_BOOMERANG, true))           ||
                (itemName == RG_KOKIRI_SWORD           && ctx->CheckEquipment(EQUIP_FLAG_SWORD_KOKIRI))         ||
                (itemName == RG_STICKS                 && ctx->CheckInventory(ITEM_STICK, true))              ||
                (itemName == RG_DEKU_SHIELD            && ctx->CheckEquipment(EQUIP_FLAG_SHIELD_DEKU))          ||
                (itemName == RG_FIRE_ARROWS            && ctx->CheckInventory(ITEM_ARROW_FIRE, true))          ||
                (itemName == RG_ICE_ARROWS             && ctx->CheckInventory(ITEM_ARROW_ICE, true))           ||
                (itemName == RG_LIGHT_ARROWS           && ctx->CheckInventory(ITEM_ARROW_LIGHT, true))         ||
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
                // Dungeon Rewards
                (itemName == RG_KOKIRI_EMERALD         && ctx->CheckQuestItem(QUEST_KOKIRI_EMERALD)) ||
                (itemName == RG_GORON_RUBY             && ctx->CheckQuestItem(QUEST_GORON_RUBY)) ||
                (itemName == RG_ZORA_SAPPHIRE          && ctx->CheckQuestItem(QUEST_ZORA_SAPPHIRE)) ||
                (itemName == RG_FOREST_MEDALLION       && ctx->CheckQuestItem(QUEST_MEDALLION_FOREST)) ||
                (itemName == RG_FIRE_MEDALLION         && ctx->CheckQuestItem(QUEST_MEDALLION_FIRE)) ||
                (itemName == RG_WATER_MEDALLION        && ctx->CheckQuestItem(QUEST_MEDALLION_WATER)) ||
                (itemName == RG_SPIRIT_MEDALLION       && ctx->CheckQuestItem(QUEST_MEDALLION_SPIRIT)) ||
                (itemName == RG_SHADOW_MEDALLION       && ctx->CheckQuestItem(QUEST_MEDALLION_SHADOW)) ||
                // Ocarina Buttons
                (itemName == RG_OCARINA_A_BUTTON       && ctx->CheckRandoInf(RAND_INF_HAS_OCARINA_A))      ||
                (itemName == RG_OCARINA_C_LEFT_BUTTON  && ctx->CheckRandoInf(RAND_INF_HAS_OCARINA_C_LEFT))  ||
                (itemName == RG_OCARINA_C_RIGHT_BUTTON && ctx->CheckRandoInf(RAND_INF_HAS_OCARINA_C_RIGHT)) ||
                (itemName == RG_OCARINA_C_DOWN_BUTTON  && ctx->CheckRandoInf(RAND_INF_HAS_OCARINA_C_DOWN))  ||
                (itemName == RG_OCARINA_C_UP_BUTTON    && ctx->CheckRandoInf(RAND_INF_HAS_OCARINA_C_UP))  ||
                // Boss Souls
                (itemName == RG_GOHMA_SOUL             && ctx->CheckRandoInf(RAND_INF_GOHMA_SOUL))  ||
                (itemName == RG_KING_DODONGO_SOUL      && ctx->CheckRandoInf(RAND_INF_KING_DODONGO_SOUL))  ||
                (itemName == RG_BARINADE_SOUL          && ctx->CheckRandoInf(RAND_INF_GOHMA_SOUL))  ||
                (itemName == RG_PHANTOM_GANON_SOUL     && ctx->CheckRandoInf(RAND_INF_PHANTOM_GANON_SOUL))  ||
                (itemName == RG_VOLVAGIA_SOUL          && ctx->CheckRandoInf(RAND_INF_VOLVAGIA_SOUL))  ||
                (itemName == RG_MORPHA_SOUL            && ctx->CheckRandoInf(RAND_INF_MORPHA_SOUL))  ||
                (itemName == RG_BONGO_BONGO_SOUL       && ctx->CheckRandoInf(RAND_INF_BONGO_BONGO_SOUL))  ||
                (itemName == RG_TWINROVA_SOUL          && ctx->CheckRandoInf(RAND_INF_TWINROVA_SOUL))  ||
                (itemName == RG_GANON_SOUL             && (ctx->GetOption(RSK_SHUFFLE_BOSS_SOULS).Is(RO_BOSS_SOULS_ON_PLUS_GANON) ? HasItem(RG_GANON_SOUL) : true)) ||
                // Boss Keys
                (itemName == RG_FOREST_TEMPLE_BOSS_KEY && ctx->CheckDungeonItem(DUNGEON_KEY_BOSS, SCENE_FOREST_TEMPLE)) ||
                (itemName == RG_FIRE_TEMPLE_BOSS_KEY   && ctx->CheckDungeonItem(DUNGEON_KEY_BOSS, SCENE_FIRE_TEMPLE)) ||
                (itemName == RG_WATER_TEMPLE_BOSS_KEY  && ctx->CheckDungeonItem(DUNGEON_KEY_BOSS, SCENE_WATER_TEMPLE)) ||
                (itemName == RG_SPIRIT_TEMPLE_BOSS_KEY && ctx->CheckDungeonItem(DUNGEON_KEY_BOSS, SCENE_SPIRIT_TEMPLE)) ||
                (itemName == RG_SHADOW_TEMPLE_BOSS_KEY && ctx->CheckDungeonItem(DUNGEON_KEY_BOSS, SCENE_SHADOW_TEMPLE)) ||
                (itemName == RG_GANONS_CASTLE_BOSS_KEY && ctx->CheckDungeonItem(DUNGEON_KEY_BOSS, SCENE_INSIDE_GANONS_CASTLE));
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
            case RG_RUTOS_LETTER:
                return IsChild;
            case RG_ZELDAS_LETTER:
                return IsChild;
            case RG_WEIRD_EGG:
                return IsChild;

            // Songs
            case RG_ZELDAS_LULLABY:
                return HasItem(RG_FAIRY_OCARINA) && HasItem(RG_OCARINA_C_LEFT_BUTTON) && HasItem(RG_OCARINA_C_RIGHT_BUTTON) && HasItem(RG_OCARINA_C_UP_BUTTON);
            case RG_EPONAS_SONG:
                return HasItem(RG_FAIRY_OCARINA) && HasItem(RG_OCARINA_C_LEFT_BUTTON) && HasItem(RG_OCARINA_C_RIGHT_BUTTON) && HasItem(RG_OCARINA_C_UP_BUTTON);
            case RG_SARIAS_SONG:
                return HasItem(RG_FAIRY_OCARINA) && HasItem(RG_OCARINA_C_LEFT_BUTTON) && HasItem(RG_OCARINA_C_RIGHT_BUTTON) && HasItem(RG_OCARINA_C_DOWN_BUTTON);
            case RG_SUNS_SONG:
                return HasItem(RG_FAIRY_OCARINA) && HasItem(RG_OCARINA_C_RIGHT_BUTTON) && HasItem(RG_OCARINA_C_UP_BUTTON) && HasItem(RG_OCARINA_C_DOWN_BUTTON);
            case RG_SONG_OF_TIME:
                return HasItem(RG_FAIRY_OCARINA) && HasItem(RG_OCARINA_A_BUTTON) && HasItem(RG_OCARINA_C_RIGHT_BUTTON) && HasItem(RG_OCARINA_C_DOWN_BUTTON);
            case RG_SONG_OF_STORMS:
                return HasItem(RG_FAIRY_OCARINA) && HasItem(RG_OCARINA_A_BUTTON) && HasItem(RG_OCARINA_C_UP_BUTTON) && HasItem(RG_OCARINA_C_DOWN_BUTTON);
            case RG_MINUET_OF_FOREST:
                return HasItem(RG_FAIRY_OCARINA) && HasItem(RG_OCARINA_A_BUTTON) && HasItem(RG_OCARINA_C_LEFT_BUTTON) && HasItem(RG_OCARINA_C_RIGHT_BUTTON) && HasItem(RG_OCARINA_C_UP_BUTTON);
            case RG_BOLERO_OF_FIRE:
                return HasItem(RG_FAIRY_OCARINA) && HasItem(RG_OCARINA_A_BUTTON) && HasItem(RG_OCARINA_C_RIGHT_BUTTON) && HasItem(RG_OCARINA_C_DOWN_BUTTON);
            case RG_SERENADE_OF_WATER:
                return HasItem(RG_FAIRY_OCARINA) && HasItem(RG_OCARINA_A_BUTTON) && HasItem(RG_OCARINA_C_LEFT_BUTTON) && HasItem(RG_OCARINA_C_RIGHT_BUTTON) && HasItem(RG_OCARINA_C_DOWN_BUTTON);
            case RG_REQUIEM_OF_SPIRIT:
                return HasItem(RG_FAIRY_OCARINA) && HasItem(RG_OCARINA_A_BUTTON) && HasItem(RG_OCARINA_C_RIGHT_BUTTON) && HasItem(RG_OCARINA_C_DOWN_BUTTON);
            case RG_NOCTURNE_OF_SHADOW:
                return HasItem(RG_FAIRY_OCARINA) && HasItem(RG_OCARINA_A_BUTTON) && HasItem(RG_OCARINA_C_LEFT_BUTTON) && HasItem(RG_OCARINA_C_RIGHT_BUTTON) && HasItem(RG_OCARINA_C_DOWN_BUTTON);
            case RG_PRELUDE_OF_LIGHT:
                return HasItem(RG_FAIRY_OCARINA) && HasItem(RG_OCARINA_C_LEFT_BUTTON) && HasItem(RG_OCARINA_C_RIGHT_BUTTON) && HasItem(RG_OCARINA_C_UP_BUTTON);

            // Magic items
            default:
                if (IsMagicItem(itemName) || (IsMagicArrow(itemName) && CanUse(RG_FAIRY_BOW))) {
                    return MagicMeter;
                } else {
                    return true;
                }
        }
    }

    bool Logic::HasProjectile(HasProjectileAge age) {
        return HasExplosives ||
               (age == HasProjectileAge::Child  && (Slingshot || CanUse(RG_BOOMERANG))) ||
               (age == HasProjectileAge::Adult  && (CanUse(RG_HOOKSHOT)  || Bow      )) ||
               (age == HasProjectileAge::Both   && (Slingshot || CanUse(RG_BOOMERANG))  && (CanUse(RG_HOOKSHOT) || Bow)) ||
               (age == HasProjectileAge::Either && (Slingshot || CanUse(RG_BOOMERANG)   ||  CanUse(RG_HOOKSHOT) || Bow));
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
                    HasItem(RG_FAIRY_SLINGSHOT) || HasItem(RG_BOOMERANG) || HasBottle || Nuts || HasItem(RG_FAIRY_OCARINA) || HasItem(RG_LENS_OF_TRUTH) || HasExplosives ||
                    (HasItem(RG_MAGIC_BEAN)) || HasItem(RG_DINS_FIRE) || HasItem(RG_FARORES_WIND) || HasItem(RG_NAYRUS_LOVE)))) && false; //GlitchEquipSwap;
        }

        //Shouldn't be reached
        return false;
    }

    Logic::Logic() {
        
    }

    // Updates all logic helpers. Should be called whenever a non-helper is changed
    void Logic::UpdateHelpers() {
        auto ctx = Rando::Context::GetInstance();
        OcarinaButtons  =  (HasItem(RG_OCARINA_A_BUTTON) ? 1 : 0) +
                           (HasItem(RG_OCARINA_C_LEFT_BUTTON) ? 1 : 0) +
                           (HasItem(RG_OCARINA_C_RIGHT_BUTTON) ? 1 : 0) +
                           (HasItem(RG_OCARINA_C_UP_BUTTON) ? 1 : 0) +
                           (HasItem(RG_OCARINA_C_DOWN_BUTTON) ? 1 : 0);
        NumBottles      = (ctx->GetSaveContext()->inventory.items[SLOT_BOTTLE_1] != ITEM_NONE && ctx->GetSaveContext()->inventory.items[SLOT_BOTTLE_1] != ITEM_LETTER_RUTO ? 1 : 0) +
                          (ctx->GetSaveContext()->inventory.items[SLOT_BOTTLE_2] != ITEM_NONE && ctx->GetSaveContext()->inventory.items[SLOT_BOTTLE_2] != ITEM_LETTER_RUTO ? 1 : 0) +
                          (ctx->GetSaveContext()->inventory.items[SLOT_BOTTLE_3] != ITEM_NONE && ctx->GetSaveContext()->inventory.items[SLOT_BOTTLE_3] != ITEM_LETTER_RUTO ? 1 : 0) +
                          (ctx->GetSaveContext()->inventory.items[SLOT_BOTTLE_4] != ITEM_NONE && ctx->GetSaveContext()->inventory.items[SLOT_BOTTLE_4] != ITEM_LETTER_RUTO ? 1 : 0) +
                          (ctx->CheckEventChkInf(EVENTCHKINF_KING_ZORA_MOVED) ? 1 : 0);
        HasBottle       = NumBottles >= 1;
        Slingshot       = (ProgressiveBulletBag >= 1) && (BuySeed || AmmoCanDrop);
        MagicMeter      = (ProgressiveMagic     >= 1) && (AmmoCanDrop || (HasBottle && BuyMagicPotion));
        BombBag         = (ProgressiveBombBag   >= 1) && (BuyBomb || AmmoCanDrop);
        Bow             = (ProgressiveBow       >= 1) && (BuyArrow || AmmoCanDrop);
        GoronBracelet   = ProgressiveStrength   >= 1;
        SilverGauntlets = ProgressiveStrength   >= 2;
        GoldenGauntlets = ProgressiveStrength   >= 3;
        SilverScale     = ProgressiveScale      >= 1;
        GoldScale       = ProgressiveScale      >= 2;
        AdultsWallet    = ProgressiveWallet     >= 1;
        //BiggoronSword   = CanUse(RG_BIGGORON_SWORD) || ProgressiveGiantKnife >= 2;

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

        FoundBombchus   = HasItem(RG_PROGRESSIVE_BOMBCHUS);
        CanPlayBowling  = (ctx->GetOption(RSK_BOMBCHUS_IN_LOGIC) && FoundBombchus) || (!ctx->GetOption(RSK_BOMBCHUS_IN_LOGIC) && BombBag);
        // TODO: Implement Ammo Drop Setting in place of bombchu drops
        HasBombchus = (BuyBombchus || (ctx->GetOption(RSK_ENABLE_BOMBCHU_DROPS).Is(RO_AMMO_DROPS_ON/*_PLUS_BOMBCHU*/) && FoundBombchus));

        HasExplosives =  Bombs || (ctx->GetOption(RSK_BOMBCHUS_IN_LOGIC) && HasBombchus);

        HasBoots = CanUse(RG_IRON_BOOTS) || CanUse(RG_HOVER_BOOTS);

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
        CanChildAttack  = IsChild && (Slingshot || CanUse(RG_BOOMERANG) || Sticks || CanUse(RG_KOKIRI_SWORD) || HasExplosives || CanUse(RG_DINS_FIRE) || CanUse(RG_MASTER_SWORD) || CanUse(RG_MEGATON_HAMMER) || CanUse(RG_BIGGORON_SWORD));
        CanChildDamage  = IsChild && (Slingshot ||              Sticks || CanUse(RG_KOKIRI_SWORD) || HasExplosives || CanUse(RG_DINS_FIRE) || CanUse(RG_MASTER_SWORD) || CanUse(RG_MEGATON_HAMMER) || CanUse(RG_BIGGORON_SWORD));
        CanAdultAttack  = IsAdult && (CanUse(RG_FAIRY_BOW) || CanUse(RG_BOOMERANG)       || CanUse(RG_STICKS) || CanUse(RG_KOKIRI_SWORD) || HasExplosives || CanUse(RG_DINS_FIRE) || CanUse(RG_MASTER_SWORD) || CanUse(RG_MEGATON_HAMMER) || CanUse(RG_BIGGORON_SWORD) || CanUse(RG_HOOKSHOT));
        CanAdultDamage  = IsAdult && (CanUse(RG_FAIRY_BOW) || CanUse(RG_STICKS)          || CanUse(RG_KOKIRI_SWORD) || HasExplosives || CanUse(RG_DINS_FIRE) || CanUse(RG_MASTER_SWORD) || CanUse(RG_MEGATON_HAMMER) || CanUse(RG_BIGGORON_SWORD));
        CanStunDeku     = CanAdultAttack || CanChildAttack || Nuts || HasShield;
        CanCutShrubs    = CanUse(RG_KOKIRI_SWORD) || CanUse(RG_BOOMERANG) || HasExplosives || CanUse(RG_MASTER_SWORD) || CanUse(RG_MEGATON_HAMMER) || CanUse(RG_BIGGORON_SWORD);
        CanDive         = ProgressiveScale >= 1;
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
        CanOpenBombGrotto   = CanBlastOrSmash       && (HasItem(RG_STONE_OF_AGONY) || ctx->GetTrickOption(RT_GROTTOS_WITHOUT_AGONY));
        CanOpenStormGrotto  = CanUse(RG_SONG_OF_STORMS) && (HasItem(RG_STONE_OF_AGONY) || ctx->GetTrickOption(RT_GROTTOS_WITHOUT_AGONY));
        HookshotOrBoomerang = CanUse(RG_HOOKSHOT) || CanUse(RG_BOOMERANG);
        CanGetNightTimeGS   = (CanUse(RG_SUNS_SONG) || !ctx->GetOption(RSK_SKULLS_SUNS_SONG));

        GuaranteeTradePath     = ctx->GetOption(RSK_SHUFFLE_INTERIOR_ENTRANCES) || ctx->GetOption(RSK_SHUFFLE_OVERWORLD_ENTRANCES) || ctx->GetTrickOption(RT_DMT_BOLERO_BIGGORON) || CanBlastOrSmash || StopGCRollingGoronAsAdult;
        //GuaranteeHint          = (hints == "Mask" && MaskofTruth) || (hints == "Agony") || (hints != "Mask" && hints != "Agony");
        HasFireSource          = CanUse(RG_DINS_FIRE) || CanUse(RG_FIRE_ARROWS);
        HasFireSourceWithTorch = HasFireSource || CanUse(RG_STICKS);

        //Gerudo Fortress
        CanFinishGerudoFortress = (ctx->GetOption(RSK_GERUDO_FORTRESS).Is(RO_GF_NORMAL)    && GerudoFortressKeys >= 4 && (CanUse(RG_KOKIRI_SWORD) || CanUse(RG_MASTER_SWORD) || CanUse(RG_BIGGORON_SWORD)) && (HasItem(RG_GERUDO_MEMBERSHIP_CARD) || CanUse(RG_FAIRY_BOW) || CanUse(RG_HOOKSHOT) || CanUse(RG_HOVER_BOOTS) || ctx->GetTrickOption(RT_GF_KITCHEN))) ||
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
        MedallionCount        = (ctx->CheckQuestItem(QUEST_MEDALLION_FOREST) ? 1:0) + (ctx->CheckQuestItem(QUEST_MEDALLION_FIRE) ? 1:0) + (ctx->CheckQuestItem(QUEST_MEDALLION_WATER) ? 1:0) + (ctx->CheckQuestItem(QUEST_MEDALLION_SPIRIT) ? 1:0) + (ctx->CheckQuestItem(QUEST_MEDALLION_SHADOW) ? 1:0) + (ctx->CheckQuestItem(QUEST_MEDALLION_LIGHT) ? 1:0);
        StoneCount            = (ctx->CheckQuestItem(QUEST_KOKIRI_EMERALD) ? 1:0) + (ctx->CheckQuestItem(QUEST_GORON_RUBY) ? 1:0) + (ctx->CheckQuestItem(QUEST_ZORA_SAPPHIRE) ? 1:0);
        DungeonCount          = (DekuTreeClear ? 1:0) + (DodongosCavernClear ? 1:0) + (JabuJabusBellyClear ? 1:0) + (ForestTempleClear ? 1:0) + (FireTempleClear ? 1:0) + (WaterTempleClear ? 1:0) + (SpiritTempleClear ? 1:0) + (ShadowTempleClear ? 1:0);
        HasAllStones          = StoneCount == 3;
        HasAllMedallions      = MedallionCount == 6;
        GregInBridgeLogic     = ctx->GetOption(RSK_BRIDGE_OPTIONS).Is(RO_BRIDGE_GREG);
        GregInLacsLogic       = ctx->GetOption(RSK_LACS_OPTIONS).Is(RO_LACS_GREG_REWARD);

        CanBuildRainbowBridge = ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_ALWAYS_OPEN)                                                                         ||
                                (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_VANILLA)    && HasItem(RG_SHADOW_MEDALLION) && HasItem(RG_SPIRIT_MEDALLION) && CanUse(RG_LIGHT_ARROWS))             ||
                                (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_STONES)     && StoneCount + (HasItem(RG_GREG_RUPEE) && GregInBridgeLogic ? 1 : 0) >= ctx->GetOption(RSK_RAINBOW_BRIDGE_STONE_COUNT).Value<uint8_t>())                    ||
                                (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_MEDALLIONS) && MedallionCount + (HasItem(RG_GREG_RUPEE) && GregInBridgeLogic ? 1 : 0) >= ctx->GetOption(RSK_RAINBOW_BRIDGE_MEDALLION_COUNT).Value<uint8_t>())            ||
                                (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_DUNGEON_REWARDS)    && StoneCount + MedallionCount + (HasItem(RG_GREG_RUPEE) && GregInBridgeLogic ? 1 : 0) >= ctx->GetOption(RSK_RAINBOW_BRIDGE_REWARD_COUNT).Value<uint8_t>())  ||
                                (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_DUNGEONS)   && DungeonCount + (HasItem(RG_GREG_RUPEE) && GregInBridgeLogic ? 1 : 0) >= ctx->GetOption(RSK_RAINBOW_BRIDGE_DUNGEON_COUNT).Value<uint8_t>())                ||
                                (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_TOKENS)     && GoldSkulltulaTokens >= ctx->GetOption(RSK_RAINBOW_BRIDGE_TOKEN_COUNT).Value<uint8_t>()) ||
                                (ctx->GetOption(RSK_RAINBOW_BRIDGE).Is(RO_BRIDGE_GREG)       && HasItem(RG_GREG_RUPEE));

        CanTriggerLACS = (ctx->GetSettings()->LACSCondition() == RO_LACS_VANILLA    && HasItem(RG_SHADOW_MEDALLION) && HasItem(RG_SPIRIT_MEDALLION))                          ||
                            (ctx->GetSettings()->LACSCondition() == RO_LACS_STONES     && StoneCount + (HasItem(RG_GREG_RUPEE) && GregInLacsLogic ? 1 : 0) >= ctx->GetOption(RSK_LACS_STONE_COUNT).Value<uint8_t>())                    ||
                            (ctx->GetSettings()->LACSCondition() == RO_LACS_MEDALLIONS && MedallionCount + (HasItem(RG_GREG_RUPEE) && GregInLacsLogic ? 1 : 0) >= ctx->GetOption(RSK_LACS_MEDALLION_COUNT).Value<uint8_t>())            ||
                            (ctx->GetSettings()->LACSCondition() == RO_LACS_REWARDS    && StoneCount + MedallionCount + (HasItem(RG_GREG_RUPEE) && GregInLacsLogic ? 1 : 0) >= ctx->GetOption(RSK_LACS_REWARD_COUNT).Value<uint8_t>())  ||
                            (ctx->GetSettings()->LACSCondition() == RO_LACS_DUNGEONS   && DungeonCount + (HasItem(RG_GREG_RUPEE) && GregInLacsLogic ? 1 : 0) >= ctx->GetOption(RSK_LACS_DUNGEON_COUNT).Value<uint8_t>())                ||
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
                return Context::GetInstance()->GetSmallKeyCount(SCENE_FOREST_TEMPLE) >= requiredAmountGlitchless;

            case RR_FIRE_TEMPLE:
                /*if (IsGlitched && (GetDifficultyValueFromString(GlitchLedgeClip) >= static_cast<uint8_t>(GlitchDifficulty::INTERMEDIATE) || GetDifficultyValueFromString(GlitchHover) >= static_cast<uint8_t>(GlitchDifficulty::INTERMEDIATE))) {
                    return FireTempleKeys >= requiredAmountGlitched;
                }*/
                return Context::GetInstance()->GetSmallKeyCount(SCENE_FOREST_TEMPLE) >= requiredAmountGlitchless;

            case RR_WATER_TEMPLE:
                /*if (IsGlitched && (false)) {
                    return WaterTempleKeys >= requiredAmountGlitched;
                }*/
                return Context::GetInstance()->GetSmallKeyCount(SCENE_FOREST_TEMPLE) >= requiredAmountGlitchless;

            case RR_SPIRIT_TEMPLE:
                /*if (IsGlitched && (false)) {
                    return SpiritTempleKeys >= requiredAmountGlitched;
                }*/
                return Context::GetInstance()->GetSmallKeyCount(SCENE_FOREST_TEMPLE) >= requiredAmountGlitchless;

            case RR_SHADOW_TEMPLE:
                /*if (IsGlitched && (GetDifficultyValueFromString(GlitchHookshotClip) >= static_cast<uint8_t>(GlitchDifficulty::NOVICE))) {
                    return ShadowTempleKeys >= requiredAmountGlitched;
                }*/
                return Context::GetInstance()->GetSmallKeyCount(SCENE_FOREST_TEMPLE) >= requiredAmountGlitchless;

            case RR_BOTTOM_OF_THE_WELL:
                /*if (IsGlitched && (false)) {
                    return BottomOfTheWellKeys >= requiredAmountGlitched;
                }*/
                return Context::GetInstance()->GetSmallKeyCount(SCENE_FOREST_TEMPLE) >= requiredAmountGlitchless;

            case RR_GERUDO_TRAINING_GROUNDS:
                /*if (IsGlitched && (false)) {
                    return GerudoTrainingGroundsKeys >= requiredAmountGlitched;
                }*/
                return Context::GetInstance()->GetSmallKeyCount(SCENE_FOREST_TEMPLE) >= requiredAmountGlitchless;

            case RR_GANONS_CASTLE:
                /*if (IsGlitched && (false)) {
                    return GanonsCastleKeys >= requiredAmountGlitched;
                }*/
                return Context::GetInstance()->GetSmallKeyCount(SCENE_FOREST_TEMPLE) >= requiredAmountGlitchless;

            case RR_MARKET_TREASURE_CHEST_GAME:
                /*if (IsGlitched && (false)) {
                    return TreasureGameKeys >= requiredAmountGlitched;
                }*/
                return Context::GetInstance()->GetSmallKeyCount(SCENE_FOREST_TEMPLE) >= requiredAmountGlitchless;

            default:
                return false;
        }
    }

    //you need at least 2 buttons for scarecrow song
    bool Logic::ScarecrowSong() {
        return (Context::GetInstance()->GetOption(RSK_SKIP_SCARECROWS_SONG) && HasItem(RG_FAIRY_OCARINA) && OcarinaButtons >= 2) ||
            (ChildScarecrow && AdultScarecrow);
    }
                           
    bool Logic::Scarecrow() {
        return HasItem(RG_HOOKSHOT) && ScarecrowSong();
    }

    bool Logic::DistantScarecrow() {
        return HasItem(RG_LONGSHOT) && ScarecrowSong();
    }

    void Logic::Reset() {
        auto ctx = Rando::Context::GetInstance();
        //Settings-dependent variables
        IsKeysanity = ctx->GetOption(RSK_KEYSANITY).Is(RO_DUNGEON_ITEM_LOC_ANYWHERE) || 
                    ctx->GetOption(RSK_KEYSANITY).Is(RO_DUNGEON_ITEM_LOC_ANYWHERE) || 
                    ctx->GetOption(RSK_KEYSANITY).Is(RO_DUNGEON_ITEM_LOC_ANYWHERE);
        AmmoCanDrop = /*AmmoDrops.IsNot(AMMODROPS_NONE) TODO: AmmoDrop setting*/ true;

        //Child item logic
        HasBottle     = false;
        Bombchus5     = false;
        Bombchus10    = false;
        Bombchus20    = false;
        SkullMask     = false;
        MaskOfTruth   = false;

        //Adult logic
        Epona         = false;
        BigPoe        = false;

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
        GregInBridgeLogic = false;
        GregInLacsLogic = false;

        //Progressive Items
        ProgressiveBulletBag  = 0;
        ProgressiveBombBag    = 0;
        ProgressiveMagic      = 0;
        ProgressiveScale      = 0;
        ProgressiveBow        = 0;
        ProgressiveWallet     = 0;
        ProgressiveStrength   = 0;
        ProgressiveOcarina    = 0;
        ProgressiveGiantKnife = 0;

        //Keys
        ForestTempleKeys          = 0;
        //If not keysanity, start with 1 logical key to account for automatically unlocking the basement door in vanilla FiT
        FireTempleKeys            = IsKeysanity || ctx->GetDungeon(Rando::FIRE_TEMPLE)->IsMQ() ? 0 : 1;
        WaterTempleKeys           = 0;
        SpiritTempleKeys          = 0;
        ShadowTempleKeys          = 0;
        GanonsCastleKeys          = 0;
        GerudoFortressKeys        = 0;
        GerudoTrainingGroundsKeys = 0;
        BottomOfTheWellKeys       = 0;
        TreasureGameKeys          = 0;

        //Gold Skulltula Count
        GoldSkulltulaTokens = 0;

        //Bottle Count
        Bottles    = 0;
        NumBottles = 0;
        NoBottles  = false;

        //Triforce Pieces
        TriforcePieces = 0;

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
        BombBag          = false;
        MagicMeter       = false;
        Bow              = false;
        GoronBracelet    = false;
        SilverGauntlets  = false;
        GoldenGauntlets  = false;
        SilverScale      = false;
        GoldScale        = false;
        AdultsWallet     = false;

        ChildScarecrow   = false;
        AdultScarecrow   = false;

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
        CanOpenBombGrotto   = false;
        CanOpenStormGrotto  = false;
        BigPoeKill          = false;
        HookshotOrBoomerang = false;

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
    }
}
