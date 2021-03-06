
#include "DBLuaClient.h"

#include <game/dbsrv/config/ConfigMgr.h>
#include <game/dbsrv/ProtoImporter.h>
#include <game/dbsrv/Util.h>

#include <mysdk/net/EventLoop.h>
#include <mysdk/net/InetAddress.h>

using namespace mysdk;
using namespace mysdk::net;

int main(int argc, char* argv[])
{

	  if (argc > 2)
	  {
		  Logger::setLogLevel(Logger::INFO);
		  unsigned short port = static_cast<unsigned short>(atoi(argv[2]));
		  EventLoop loop;
		  InetAddress serverAddr(argv[1], port);

		    // import proto file
			std::string filenames = sConfigMgr.MainConfig.GetStringDefault("proto", "filelist", "game.proto");
			std::vector<std::string> vec = StrSplit(filenames, ",");
			for (size_t i = 0; i < vec.size(); i++)
			{
				sProtoImporter.Import(vec[i]);
			}

		  DBLuaClient client(&loop, serverAddr);
		  client.connect();
		  loop.loop();
	  }
	  else
	  {
		  printf("Usage: %s host_ip port\n", argv[0]);
	  }
	return 0;
}
