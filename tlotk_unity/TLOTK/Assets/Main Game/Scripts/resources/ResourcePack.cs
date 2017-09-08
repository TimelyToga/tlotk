using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class ResourcePack
{
	private float totalUnits;
	private Dictionary<EResource, Resource> resources = new Dictionary<EResource, Resource>();

	public ResourcePack() {
		
	}

	public void addResource(Resource resource) {
		resources[resource.resType] = resource;
		totalUnits += resource.amount;
	}

	public bool contains(EResource res) {
		return resources.TryGetValue (res);
	}

	public List<EResource> getResourcesKeys() {
		return resources.Keys;
	}

	public ResourcePack getBalancedSample(float amount) {
		ResourcePack output = new ResourcePack ();

		// For key in keys 

		// Figure out resource proportion

		// Extract that resource amount into output
		return output;
	}

	// Update is called once per frame
	void Update ()
	{
		
	}
}

