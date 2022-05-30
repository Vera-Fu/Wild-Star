
#include <nn/atk.h>
#include <nns/atk/atk_SampleCommon.h>

#include "main.h"
#include "sound.h"


namespace
{
    const char ArchiveRelativePath[] = "SOUND.bfsar";

    const int SoundHeapSize = 4 * 1024 * 1024;

    nn::atk::SoundHeap          g_SoundHeap;
    nn::atk::FsSoundArchive     g_SoundArchive;
    nn::atk::SoundArchivePlayer g_SoundArchivePlayer;
    nn::atk::SoundDataManager   g_SoundDataManager;

    nn::audio::MemoryPoolType   g_MemoryPool;

    void* g_pMemoryForSoundSystem;
    void* g_pMemoryForSoundHeap;
    void* g_pMemoryForInfoBlock;
    void* g_pMemoryForSoundDataManager;
    void* g_pMemoryForSoundArchivePlayer;
    void* g_pMemoryForStreamBuffer;

    nn::atk::SoundHandle        g_SoundHandleBGM;
    nn::atk::SoundHandle        g_SoundHandleSE;
}



void InitSound()
{

 	// SoundSystem初期化
	{
		nns::atk::InitializeHeap();
		nns::atk::InitializeFileSystem();


		bool isSuccess = true;

		nn::atk::SoundSystem::SoundSystemParam param;
		std::size_t memSizeForSoundSystem = nn::atk::SoundSystem::GetRequiredMemSize(param);
		g_pMemoryForSoundSystem = nns::atk::Allocate(memSizeForSoundSystem, nn::atk::SoundSystem::WorkMemoryAlignSize);
		isSuccess = nn::atk::SoundSystem::Initialize(
			param,
			reinterpret_cast<uintptr_t>(g_pMemoryForSoundSystem),
			memSizeForSoundSystem);
		NN_ABORT_UNLESS(isSuccess, "cannot initialize SoundSystem");

		// SoundHeap の初期化
		g_pMemoryForSoundHeap = nns::atk::Allocate(SoundHeapSize);
		isSuccess = g_SoundHeap.Create(g_pMemoryForSoundHeap, SoundHeapSize);
		NN_ABORT_UNLESS(isSuccess, "cannot create SoundHeap");

		// SoundArchive の初期化
		const char* archiveAbsolutePath = nns::atk::GetAbsolutePath(ArchiveRelativePath);
		isSuccess = g_SoundArchive.Open(archiveAbsolutePath);
		NN_ABORT_UNLESS(isSuccess, "cannot open SoundArchive(%s)\n", archiveAbsolutePath);

		// SoundArchive のパラメータ情報をメモリにロード
		std::size_t infoBlockSize = g_SoundArchive.GetHeaderSize();
		g_pMemoryForInfoBlock = nns::atk::Allocate(infoBlockSize, nn::atk::FsSoundArchive::BufferAlignSize);
		isSuccess = g_SoundArchive.LoadHeader(g_pMemoryForInfoBlock, infoBlockSize);
		NN_ABORT_UNLESS(isSuccess, "cannot load InfoBlock");

		// SoundDataManager の初期化
		std::size_t memSizeForSoundDataManager = g_SoundDataManager.GetRequiredMemSize(&g_SoundArchive);
		g_pMemoryForSoundDataManager = nns::atk::Allocate(memSizeForSoundDataManager, nn::atk::SoundDataManager::BufferAlignSize);
		isSuccess = g_SoundDataManager.Initialize(
			&g_SoundArchive,
			g_pMemoryForSoundDataManager,
			memSizeForSoundDataManager);
		NN_ABORT_UNLESS(isSuccess, "cannot initialize SoundDataManager");

		// SoundArchivePlayer で用いるストリームバッファの初期化
		// ストリームバッファはメモリプール管理されているヒープから確保する必要があります。
		std::size_t memSizeForStreamBuffer = g_SoundArchivePlayer.GetRequiredStreamBufferSize(&g_SoundArchive);
		g_pMemoryForStreamBuffer = nns::atk::AllocateForMemoryPool(memSizeForStreamBuffer);

		// 専用のヒープをメモリプールにアタッチ
		nn::atk::SoundSystem::AttachMemoryPool(&g_MemoryPool, nns::atk::GetPoolHeapAddress(), nns::atk::GetPoolHeapSize());

		// SoundArchivePlayer の初期化
		std::size_t memSizeForSoundArchivePlayer = g_SoundArchivePlayer.GetRequiredMemSize(&g_SoundArchive);
		g_pMemoryForSoundArchivePlayer = nns::atk::Allocate(memSizeForSoundArchivePlayer, nn::atk::SoundArchivePlayer::BufferAlignSize);
		isSuccess = g_SoundArchivePlayer.Initialize(
			&g_SoundArchive,
			&g_SoundDataManager,
			g_pMemoryForSoundArchivePlayer, memSizeForSoundArchivePlayer,
			g_pMemoryForStreamBuffer, memSizeForStreamBuffer);
		NN_ABORT_UNLESS(isSuccess, "cannot initialize SoundArchivePlayer");
	}



	// SoundData読み込み
	{
		bool isSuccess = true;

		isSuccess = g_SoundDataManager.LoadData(WSD_SE_BULLET01, &g_SoundHeap);
		NN_ABORT_UNLESS(isSuccess, "LoadData failed.");

		isSuccess = g_SoundDataManager.LoadData(WSD_SE_BULLET02, &g_SoundHeap);
		NN_ABORT_UNLESS(isSuccess, "LoadData failed.");

		isSuccess = g_SoundDataManager.LoadData(WSD_SE_BULLET03, &g_SoundHeap);
		NN_ABORT_UNLESS(isSuccess, "LoadData failed.");

		isSuccess = g_SoundDataManager.LoadData(WSD_SE_CLICK, &g_SoundHeap);
		NN_ABORT_UNLESS(isSuccess, "LoadData failed.");
		
		isSuccess = g_SoundDataManager.LoadData(WSD_SE_EXPLOSION1, &g_SoundHeap);
		NN_ABORT_UNLESS(isSuccess, "LoadData failed.");

		isSuccess = g_SoundDataManager.LoadData(WSD_SE_EXPLOSION2, &g_SoundHeap);
		NN_ABORT_UNLESS(isSuccess, "LoadData failed.");

		isSuccess = g_SoundDataManager.LoadData(WSD_SE_EXPLOSION3, &g_SoundHeap);
		NN_ABORT_UNLESS(isSuccess, "LoadData failed.");

		isSuccess = g_SoundDataManager.LoadData(WSD_SE_EXPLOSION4, &g_SoundHeap);
		NN_ABORT_UNLESS(isSuccess, "LoadData failed.");

		isSuccess = g_SoundDataManager.LoadData(WSD_SE_UIMOVE, &g_SoundHeap);
		NN_ABORT_UNLESS(isSuccess, "LoadData failed.");

		isSuccess = g_SoundDataManager.LoadData(WSD_SE_VICTORY, &g_SoundHeap);
		NN_ABORT_UNLESS(isSuccess, "LoadData failed.");
		
	}
}



void UninitSound()
{
    g_SoundArchivePlayer.Finalize();

    // 専用のヒープをメモリプールからデタッチ
    nn::atk::SoundSystem::DetachMemoryPool(&g_MemoryPool);

    g_SoundDataManager.Finalize();
    g_SoundArchive.Close();
    g_SoundHeap.Destroy();
    nn::atk::SoundSystem::Finalize();

    nns::atk::FreeForMemoryPool(g_pMemoryForStreamBuffer);
    nns::atk::Free(g_pMemoryForSoundArchivePlayer);
    nns::atk::Free(g_pMemoryForSoundDataManager);
    nns::atk::Free(g_pMemoryForInfoBlock);
    nns::atk::Free(g_pMemoryForSoundHeap);
    nns::atk::Free(g_pMemoryForSoundSystem);


	nns::atk::FinalizeFileSystem();
	nns::atk::FinalizeHeap();

}


void UpdateSound()
{
    g_SoundArchivePlayer.Update();
}


void PlayBGM(nn::atk::SoundArchive::ItemId soundId)
{
	//g_SoundArchivePlayer.StartSound(&g_SoundHandleBGM, soundId);

	nn::atk::SoundStartable::StartInfo si;
	si.enableFlag = nn::atk::SoundStartable::StartInfo::EnableFlagBit_LoopInfo;
	si.loopInfo.isLoopEnabled = true;
	si.loopInfo.enableParameterFlag = nn::atk::SoundStartable::StartInfo::LoopInfo::EnableParameterFlagBit_LoopEnabled;
	
	switch (soundId)
	{
	case STRM_BGM_LEVEL03:
		g_SoundArchivePlayer.StartSound(&g_SoundHandleBGM, soundId, &si);
		break;
	case STRM_BGM_LEVEL04:
		g_SoundArchivePlayer.StartSound(&g_SoundHandleBGM, soundId, &si);
		break;
	default:
		g_SoundArchivePlayer.StartSound(&g_SoundHandleBGM, soundId);
		break;
	}
}

void StopBGM()
{
	g_SoundHandleBGM.Stop(0);
}

void SetVolumeBGM(float volume, int delayFrame)
{
	g_SoundHandleBGM.SetVolume(volume, delayFrame);
}

void PlaySE(nn::atk::SoundArchive::ItemId soundId)
{
	g_SoundArchivePlayer.StartSound(&g_SoundHandleSE, soundId);
}

