using UnityEngine;
using System.Collections;

public class Resource
{
	public EResource resType;
	public float amount;

	public Resource(EResource type) {
		resType = type;
	}

	/*
	 * Adds a quantity of resource
	 */
	public float add(float amt) {
		return amount += amt;
	}

	/**
	 * @returns: successfully removed the material
	 */
	public bool remove(float amt) {
		if (amount >= amt) {
			amount -= amt;
			return true;
		}

		return false;
	}
}

