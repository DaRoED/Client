#pragma once

enum
{
	S_EnterGame = 1,
	S_MyPlayer = 2,
	S_AddObject = 3,
	S_RemoveObject = 4,
	C_Move = 5,
	S_Move = 6
};

class ClientPacketHandler
{
public:
	static void HandlePacket(ServerSessionRef session ,BYTE* buffer, int32 len);

	// 받기
	static void Handle_S_EnterGame(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_MyPlayer(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_AddObject(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_RemoveObject(ServerSessionRef session, BYTE* buffer, int32 len);
	static void Handle_S_Move(ServerSessionRef session, BYTE* buffer, int32 len);


	// 보내기
	static SendBufferRef Make_C_Move();


	template<typename T>
	static SendBufferRef MakeSendBuffer(T& pkt, uint16 pktId)
	{
		const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = make_shared<SendBuffer>(packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = pktId;
		assert(pkt.SerializeToArray(&header[1], dataSize));
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}
};

