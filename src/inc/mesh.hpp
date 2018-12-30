// Convert a subset of a world into a vertex array (also called a mesh). The
// generated vertex array is stored in target, and it's size (in floats) is
// stored in target_size_in_floats.

void world_subset_to_mesh
(
	world* input,

	unsigned int x,
	unsigned int y,
	unsigned int z,

	unsigned int x_res,
	unsigned int y_res,
	unsigned int z_res,

	float* target,

	unsigned int& target_size_in_floats
)
{
	float* ptr = target;

	unsigned int fx = x + x_res;
	unsigned int fy = y + y_res;
	unsigned int fz = z + z_res;

	for (unsigned int cx = x; cx < fx; cx++)
	{
		for (unsigned int cy = y; cy < fy; cy++)
		{
			for (unsigned int cz = z; cz < fz; cz++)
			{
				// Skip voxels that are out of bounds.

				if (!input->in_bounds(cx, cy, cz))
				{
					continue;
				}

				// Get the current voxel's block_id.

				block_id voxel_id = input->get_id(cx, cy, cz);

				// Ignore voxels that have a block_id equivalent to id_air.
				// Voxels that have a block_id equivalent to id_air are fully
				// transparent, and do not need to be rendered.

				if (voxel_id == id_air)
				{
					continue;
				}

				// Get the face_info* object that matches the block_id of the
				// current voxel.

				face_info* cube_face_info = block_face_info[voxel_id];

				// Get the layer index corresponding to each face of the 
				// current voxel.

				float layer_top = cube_face_info->l_top;

				float layer_bottom = cube_face_info->l_bottom;

				float layer_left = cube_face_info->l_left;

				float layer_right = cube_face_info->l_right;

				float layer_front = cube_face_info->l_front;

				float layer_back = cube_face_info->l_back;

				// Get the natural and artificial floating-point lighting 
				// values of the current voxel.

				float voxel_light_natural = input->get_natural(cx, cy, cz) / 15.0f;

				float voxel_light_artificial = input->get_artificial(cx, cy, cz) / 15.0f;

				// Get the final voxel floating-point lighting value by 
				// choosing the largest lighting component of the voxel.

				float voxel_light = std::max(voxel_light_natural, voxel_light_artificial);

				// Calculate the lighting value of each face by multiplying 
				// the lighting value of the current voxel by a constant
				// coefficient.

				float lighting_top = 1.0f * voxel_light;

				float lighting_bottom = 0.65f * voxel_light;

				float lighting_left = 0.75f * voxel_light;

				float lighting_right = 0.75f * voxel_light;

				float lighting_front = 0.9f * voxel_light;

				float lighting_back = 0.9f * voxel_light;

				// Do hidden face culling. This optimization will cause faces
				// that are never going to be rendered (hidden faces) to be 
				// culled.

				bool visible_top = is_transparent(input->get_id_safe(cx, cy - 1, cz));

				bool visible_bottom = is_transparent(input->get_id_safe(cx, cy + 1, cz));

				bool visible_left = is_transparent(input->get_id_safe(cx - 1, cy, cz));

				bool visible_right = is_transparent(input->get_id_safe(cx + 1, cy, cz));

				bool visible_front = is_transparent(input->get_id_safe(cx, cy, cz - 1));

				bool visible_back = is_transparent(input->get_id_safe(cx, cy, cz + 1));

				// Generate visible faces and write them to the target array,
				// using ptr as a 'stream writer'.

				if (visible_top)
				{
					*(ptr++) = 1.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 0.0f; *(ptr++) = layer_top; *(ptr++) = lighting_top;
					*(ptr++) = 0.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 1.0f; *(ptr++) = layer_top; *(ptr++) = lighting_top;
					*(ptr++) = 0.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 1.0f; *(ptr++) = layer_top; *(ptr++) = lighting_top;

					*(ptr++) = 1.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 0.0f; *(ptr++) = layer_top; *(ptr++) = lighting_top;
					*(ptr++) = 0.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 1.0f; *(ptr++) = layer_top; *(ptr++) = lighting_top;
					*(ptr++) = 1.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 0.0f; *(ptr++) = layer_top; *(ptr++) = lighting_top;
				}

				if (visible_bottom)
				{
					*(ptr++) = 0.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 0.0f; *(ptr++) = layer_bottom; *(ptr++) = lighting_bottom;
					*(ptr++) = 0.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 1.0f; *(ptr++) = layer_bottom; *(ptr++) = lighting_bottom;
					*(ptr++) = 1.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 1.0f; *(ptr++) = layer_bottom; *(ptr++) = lighting_bottom;

					*(ptr++) = 0.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 0.0f; *(ptr++) = layer_bottom; *(ptr++) = lighting_bottom;
					*(ptr++) = 1.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 1.0f; *(ptr++) = layer_bottom; *(ptr++) = lighting_bottom;
					*(ptr++) = 1.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 0.0f; *(ptr++) = layer_bottom; *(ptr++) = lighting_bottom;
				}

				if (visible_left)
				{
					*(ptr++) = 0.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 0.0f; *(ptr++) = layer_left; *(ptr++) = lighting_left;
					*(ptr++) = 0.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 1.0f; *(ptr++) = layer_left; *(ptr++) = lighting_left;
					*(ptr++) = 0.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 1.0f; *(ptr++) = layer_left; *(ptr++) = lighting_left;

					*(ptr++) = 0.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 0.0f; *(ptr++) = layer_left; *(ptr++) = lighting_left;
					*(ptr++) = 0.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 1.0f; *(ptr++) = layer_left; *(ptr++) = lighting_left;
					*(ptr++) = 0.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 0.0f; *(ptr++) = layer_left; *(ptr++) = lighting_left;
				}

				if (visible_right)
				{
					*(ptr++) = 1.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 0.0f; *(ptr++) = layer_right; *(ptr++) = lighting_right;
					*(ptr++) = 1.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 1.0f; *(ptr++) = layer_right; *(ptr++) = lighting_right;
					*(ptr++) = 1.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 1.0f; *(ptr++) = layer_right; *(ptr++) = lighting_right;

					*(ptr++) = 1.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 0.0f; *(ptr++) = layer_right; *(ptr++) = lighting_right;
					*(ptr++) = 1.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 1.0f; *(ptr++) = layer_right; *(ptr++) = lighting_right;
					*(ptr++) = 1.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 0.0f; *(ptr++) = layer_right; *(ptr++) = lighting_right;
				}

				if (visible_front)
				{
					*(ptr++) = 0.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 0.0f; *(ptr++) = layer_back; *(ptr++) = lighting_back;
					*(ptr++) = 0.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 1.0f; *(ptr++) = layer_back; *(ptr++) = lighting_back;
					*(ptr++) = 1.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 1.0f; *(ptr++) = layer_back; *(ptr++) = lighting_back;

					*(ptr++) = 0.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 0.0f; *(ptr++) = layer_back; *(ptr++) = lighting_back;
					*(ptr++) = 1.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 1.0f; *(ptr++) = layer_back; *(ptr++) = lighting_back;
					*(ptr++) = 1.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 0.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 0.0f; *(ptr++) = layer_back; *(ptr++) = lighting_back;
				}

				if (visible_back)
				{
					*(ptr++) = 1.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 0.0f; *(ptr++) = layer_front; *(ptr++) = lighting_front;
					*(ptr++) = 1.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 1.0f; *(ptr++) = layer_front; *(ptr++) = lighting_front;
					*(ptr++) = 0.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 1.0f; *(ptr++) = layer_front; *(ptr++) = lighting_front;

					*(ptr++) = 1.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 1.0f; *(ptr++) = 0.0f; *(ptr++) = layer_front; *(ptr++) = lighting_front;
					*(ptr++) = 0.0f + cx; *(ptr++) = -1.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 1.0f; *(ptr++) = layer_front; *(ptr++) = lighting_front;
					*(ptr++) = 0.0f + cx; *(ptr++) = -0.0f - cy; *(ptr++) = 1.0f + cz; *(ptr++) = 0.0f; *(ptr++) = 0.0f; *(ptr++) = layer_front; *(ptr++) = lighting_front;
				}
			}
		}
	}

	// Calculate the amount of floats that were written to target, and store
	// that value in target_size_in_floats.

	target_size_in_floats = ptr - target;
}