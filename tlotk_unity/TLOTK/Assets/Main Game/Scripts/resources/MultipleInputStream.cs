using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class MultipleInputStream : ResourceStream
{
	List<ResourceStream> streams;

	private int curStream;

	public MultipleInputStream(){ 
		streams = new List<ResourceStream> ();
		curStream = 0; 
	}

	public void add(ResourceStream r) {
		streams.Add (r);
	}

	public bool remove(ResourceStream r) {
		return streams.Remove (r);
	}

	/* 
	 * Call getSourceSample on one of the sub resources at a time
	 */
	public ResourcePack getSourceSample(float amt) {
		if (streams.Count != 0) {
			if (streams.Count >= curStream - 1) {
				curStream %= streams.Count;

				// TODO: Randomize streams
			}

			return streams [curStream++].getSourceSample(amt);
		}

		return null;
	}

	public void outputResource(ResourcePack rp) {
		// No-op
	}
}

