using System;

public interface ResourceStream
{
	ResourcePack getSourceSample(float amt);
	void outputResource(ResourcePack rp);
}

