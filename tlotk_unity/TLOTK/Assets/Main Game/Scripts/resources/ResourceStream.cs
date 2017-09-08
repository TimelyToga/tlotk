using System;

public interface ResourceStream
{
	ResourcePack resourceSource();
	void outputResource(ResourcePack rp);
}

