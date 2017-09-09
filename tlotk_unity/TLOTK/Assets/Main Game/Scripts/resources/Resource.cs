using UnityEngine;
using System.Collections;

public class Resource
{
	public EResource resType;
	public float amount = 0.0f;

	public Resource(EResource type) {
		resType = type;
	}

	public Resource(EResource type, float amt) {
		resType = type;
		amount = amt;
	}

	/*
	 * Adds a quantity of resource
	 * 
	 * @return: the new total amount
	 */
	public float add(float amt) {
		return amount += amt;
	}

	public bool hasAtLeast(float amt) {
		return amount >= amt;
	}

	/**
	 * @returns: successfully removed material
	 */
	public float remove(float amt) {
		if (amount >= amt) {
			amount -= amt;
			return amt;
		}

		float output = amount;
		amount = 0;
		return output;
	}

	public Resource removeNew(float amt) {
		float removedAmt = remove (amt);
		return new Resource (resType, removedAmt);
	}
}

