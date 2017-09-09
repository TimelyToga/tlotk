using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class ResourcePack
{
	private float totalUnits;
	private Dictionary<EResource, Resource> resources;

	public ResourcePack() {
		resources = new Dictionary<EResource, Resource> ();
	}

	public void addResource(Resource resource) {
		resources[resource.resType] = resource;
		totalUnits += resource.amount;
	}

	public bool contains(EResource res) {
		return resources.ContainsKey (res);
	}

	public Dictionary<EResource, Resource>.KeyCollection getResourcesKeys() {
		return resources.Keys;
	}

	public ResourcePack getBalancedSample(float amount) {
		ResourcePack output = new ResourcePack ();

		// For key in keys 
		var keys = getResourcesKeys();
		foreach(EResource k in keys) {
			// Figure out resource proportion
			Resource r = resources[k];
			float curAmount = (r.amount / totalUnits) * amount;

			// Extract that resource amount into output
			// Remove --> Add so material is never created 
			Resource curExtract = new Resource(k, r.remove (curAmount));
			output.addResource (curExtract);
		}
			
		return output;
	}

	Resource getSpecificSample(EResource type, float amount) {
		if (contains (type)) {
			Resource r = resources [type];
			return r.removeNew(amount);
		}

		return new Resource(type);
	}
}

