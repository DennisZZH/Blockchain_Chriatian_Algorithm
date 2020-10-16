CC = g++
PC = protoc
CFLAGS += -std=c++11
PROTOBUF_LIB := `pkg-config --cflags --libs protobuf`

message: Msg.proto
		$(PC) -I=. --cpp_out=. ./Msg.proto

client: client.cpp Msg.pb.cc utility.cpp 
		$(CC) $(CFLAGS) $^ $(PROTOBUF_LIB) -o $@

server:  server.cpp Msg.pb.cc utility.cpp
		$(CC) $(CFLAGS) $^ $(PROTOBUF_LIB) -o $@

clean:
		rm server client