// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2013-2079 Dr. Kimoto Chan
// Copyright (c) 2013-2079 The Megacoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;

#include "chainparamsseeds.h"

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60; // 3.5 days
        consensus.nPowTargetSpacing = 2.5 * 60; // 2.5 minutes
        consensus.fPowAllowMinDifficultyBlocks = false;
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xed;
        pchMessageStart[1] = 0xe0;
        pchMessageStart[2] = 0xe4;
        pchMessageStart[3] = 0xee;
        vAlertPubKey = ParseHex("04680D5270D3E6BA9E2671D889778FC4A0753FF036171D553A179635DDE67146481AB4EA7A6856CBB6A97AE16E7820F2F318E88F21E9BCFB0380E52BD63306C05C");
        nDefaultPort = 7951;
        nMinerThreads = 0;
        nPruneAfterHeight = 100000;

        /**
        // Genesis Block (Main):
+		// CBlock(hash=7520788e2d99eec, PoW=00000f308aff6ee4125a, ver=1, hashPrevBlock=00000000000000000000, hashMerkleRoot=6065d08d75, nTime=1369197853, nBits=1e0ffff0, nNonce=2084576387, vtx=1)
+		//   CTransaction(hash=6065d08d75, ver=1, vin.size=1, vout.size=1, nLockTime=0)
+		//     CTxIn(COutPoint(0000000000, -1), coinbase 04ffff001d01044c4c426f73746f6e20486572616c64202d2032312f4d61792f32303133202d20495253204f6666696369616c20746f2054616b6520466966746820746f204)
+		//     CTxOut(nValue=500.00000000, scriptPubKey=0411582e4e718df82c9d75a4886ab7)
+		//   vMerkleTree: 6065d08d75
+		
+		// Genesis Block (Test):
+		// CBlock(hash=f9e3f18eaa2404b, PoW=00000b75a3fece2f380a, ver=1, hashPrevBlock=00000000000000000000, hashMerkleRoot=6065d08d75, nTime=1369198853, nBits=1e0ffff0, nNonce=386245382, vtx=1)
+		//   CTransaction(hash=6065d08d75, ver=1, vin.size=1, vout.size=1, nLockTime=0)
+		//     CTxIn(COutPoint(0000000000, -1), coinbase 04ffff001d01044c4c426f73746f6e20486572616c64202d2032312f4d61792f32303133202d20495253204f6666696369616c20746f2054616b6520466966746820746f204)
+		//     CTxOut(nValue=500.00000000, scriptPubKey=0411582e4e718df82c9d75a4886ab7)
+		//   vMerkleTree: 6065d08d75
         */
        const char* pszTimestamp = "Boston Herald - 21/May/2013 - IRS Official to Take Fifth to Avoid Testifying";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 500 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0411582e4e718df82c9d75a4886ab7602f0a1b866d81a4e44acba04e847ccd0514b97bee4a61fa73b1474d12851422b01565f244f722f318f1608258b74a3f3fe6") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock.SetNull();
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1369197853;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 2084576387;

        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x7520788e2d99eec7cf6cf7315577e1268e177fff94cb0a7caf6a458ceeea9ac2"));
        assert(genesis.hashMerkleRoot == uint256S("0x6065d08d755e00a90449abe8a0923d0622feb6f7ab3f435c337369334119e636"));

        vSeeds.push_back(CDNSSeedData("bitcoin.sipa.be", "seed.bitcoin.sipa.be")); // Pieter Wuille
        vSeeds.push_back(CDNSSeedData("bluematt.me", "dnsseed.bluematt.me")); // Matt Corallo
        vSeeds.push_back(CDNSSeedData("dashjr.org", "dnsseed.bitcoin.dashjr.org")); // Luke Dashjr
        vSeeds.push_back(CDNSSeedData("bitcoinstats.com", "seed.bitcoinstats.com")); // Christian Decker
        vSeeds.push_back(CDNSSeedData("xf2.org", "bitseed.xf2.org")); // Jeff Garzik
        vSeeds.push_back(CDNSSeedData("bitcoin.jonasschnelli.ch", "seed.bitcoin.jonasschnelli.ch")); // Jonas Schnelli

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,50);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (Checkpoints::CCheckpointData) {
            boost::assign::map_list_of
            (   5215, uint256("0xf8a7fec79eeee3228499601c614b179d09b1b08bd58515be8a2795f6baafb493"))
			(   7333, uint256("0xf798f245214a5ed83c69d362a88c48047c82675d3bf84b0c88d6f1c71ed4b372"))
			(   9850, uint256("0x03359392dab8f47cd70626bb978c7658a385a49570bd953a1c9f8ceed4ff8be6"))
			(  10000, uint256("0xe17057f2114a45827acbcfe2a55b273ccabd3dc8982765f7a3fbca166811909b"))
			(  15480, uint256("0xf682a44431fff21c5d412f97e92f3340c59527626f6b5a4c6b85de78e009f177"))
			(  17625, uint256("0x5c4df33d72bef0c9e95bcce997e0c1d5985e957a16aebbf463a8bbee1ab9eb4b"))
			(  21190, uint256("0xe960216ff0e3ebae632af05792f0a11bf8a8f61e4f5ef43fcfd84b6e8053ec59"))
			(  35500, uint256("0xb88a54ce5d247a46166ff28228c62efc495cfb8d0dadfa895bced191cb261c90"))
			(  39500, uint256("0x3eb61d9897009caa6ed492fc154121849166d7a627f26322eae9cf32c7dc753b"))
			(  44400, uint256("0xeb5af032f88981810f31f13e38e33c86585dbf963ea6de199382706dc5b3aee4"))
			(  59300, uint256("0x558cf1f1fe31eb0816f9fc73900133564c29b50b626cbf82c69860fd3583653c"))
			(  62767, uint256("0x5bd5d25c8a19b764634435b9ab1121b4678fbf6e6ad771b252f75f3cdfa82131"))
			(  96800, uint256("0xf972b9421ac790af82cd63f5db1dbbee114ce3476486d4335f46c6d7d8897671"))
			( 106980, uint256("0x0144e525eb188106e435af296caf2bf707e174c65b1b50361b9dfeb942123cab"))
			( 184000, uint256("0x61974eed4dd83c7b4b4954593769fe1939e00d701bd5cfd17d30eeb986dae67c"))		
			( 201050, uint256("0xf6f0890c7d94ac3596fbb19050a95edaea14fca8706b2b55408fe202f413153b"))
			( 221000, uint256("0x88d40255918470d178b1f171f58543b74b130982a29eda026416ca643592132d"))
			( 241000, uint256("0x53c964a043a98d8731a4ad62e8d155a619d4f2d413d4d6352e5cba5eb6c6b786"))
			( 261300, uint256("0xcd9d91664a49bbf8c1c504420bf6ea5e2ac3a68e55344396d4bbf59162ff4261"))
			( 284000, uint256("0x5cdce62308c7e77c6aa93ab0e754116fbb14d4a0972da5b6465a31b047e47cb2"))
			( 304000, uint256("0x6ab3a605154bd90aa748ea07de6d3f98d42f32b8a56ba1d993ea0837fa28087c"))
			( 334100, uint256("0xb44d860b7332c4d235b013270dedaec9b0e8e4bfe701cc1ef322b807c41c6b7d"))
			( 392675, uint256("0x26693075b87f5b6394381fe8590cd69a93e965a66d329786a1abfe0bc2fcdc5c")),
            1397271012, // * UNIX timestamp of last checkpoint block
            709594,   // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            60000.0     // * estimated number of transactions per day after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.fPowAllowMinDifficultyBlocks = true;
        pchMessageStart[0] = 0xfd;
        pchMessageStart[1] = 0xf0;
        pchMessageStart[2] = 0xf4;
        pchMessageStart[3] = 0xfe;
        vAlertPubKey = ParseHex("04826AC11FCF383A1E0F21E2A76807D082FF4E7F139111A7768E4F5A35A5653A2D44A8E19BC8B55AEDC9F9238D424BDC5EBD6D2BAF9CB3D30CEDEA35C47C8350A0");
        nDefaultPort = 17951;
        nMinerThreads = 0;
        nPruneAfterHeight = 1000;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1369198853;
        genesis.nNonce = 386245382;
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xf9e3f18eaa2404b23c57ed9961d7e777e95a1f2c88dfd373e5ddadc8ed343cc1"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("alexykot.me", "testnet-seed.alexykot.me"));
        vSeeds.push_back(CDNSSeedData("bitcoin.petertodd.org", "testnet-seed.bitcoin.petertodd.org"));
        vSeeds.push_back(CDNSSeedData("bluematt.me", "testnet-seed.bluematt.me"));
        vSeeds.push_back(CDNSSeedData("bitcoin.schildbach.de", "testnet-seed.bitcoin.schildbach.de"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        checkpointData = (Checkpoints::CCheckpointData) {
            boost::assign::map_list_of
            ( 546, uint256S("000000002a936ca763904c3c35fce2f3556c559c0214345d31b1bcebf76acb70")),
            1337966069,
            1488,
            300
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nMinerThreads = 1;
        genesis.nTime = 1369198853;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2;
        consensus.hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        assert(consensus.hashGenesisBlock == uint256S("0x0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"));
        nPruneAfterHeight = 1000;

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (Checkpoints::CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206")),
            0,
            0,
            0
        };
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
