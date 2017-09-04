using UnityEngine;

namespace UnityStandardAssets.Utility
{
	public class SmoothFollow : MonoBehaviour
	{

		public float ZOOM_DAMP = 0.5f;
		public float minZoom = 10.0f;
		public float maxZoom = 100.0f;

		// The target we are following
		[SerializeField]
		private Transform target;
		// The distance in the x-z plane to the target
		[SerializeField]
		private float distance = 10.0f;
		// the height we want the camera to be above the target
		[SerializeField]
		private float height = 5.0f;

		[SerializeField]
		private float rotationDamping;
		[SerializeField]
		private float heightDamping;

		// Use this for initialization
		void Start() { 

		}

		void Update () {
			// Will be +/- depending on the scroll direction
			float scrollAmount = Input.GetAxis("Mouse ScrollWheel");
			float scrollPercentage = 1 + scrollAmount * ZOOM_DAMP;
			float nextZ = Camera.main.transform.position.z * scrollPercentage;

			Debug.Log (scrollAmount + ", " + scrollPercentage * 100 + "% , " + nextZ );

			Camera.main.transform.position = new Vector3(0, 0, nextZ);
		}
	}
}