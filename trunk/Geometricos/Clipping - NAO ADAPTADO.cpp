bool clip_segment(const Rect &rect, const Segment &seg, Segment &clipped_seg)
{
	clipped_seg = seg;
	for(int i = 0; i < 8; ++i) {
		int checkPosF = 0, checkPosT = 0;
		if(clipped_seg.from[0] < rect.min[0]) checkPosF |= 1; // left
		if(clipped_seg.from[0] > rect.max[0]) checkPosF |= 2; // right
		if(clipped_seg.from[1] < rect.min[1]) checkPosF |= 4; // down
		if(clipped_seg.from[1] > rect.max[1]) checkPosF |= 8; // up

		if(clipped_seg.to[0] < rect.min[0]) checkPosT |= 1; // left
		if(clipped_seg.to[0] > rect.max[0]) checkPosT |= 2; // right
		if(clipped_seg.to[1] < rect.min[1]) checkPosT |= 4; // down
		if(clipped_seg.to[1] > rect.max[1]) checkPosT |= 8; // up

		if((!checkPosF)&&(!checkPosT)) return true;
		if(checkPosF & checkPosT) return false;

		float x0 = clipped_seg.from[0], x1 = clipped_seg.to[0];
		float y0 = clipped_seg.from[1], y1 = clipped_seg.to[1];

		if(checkPosF & 1) {
			clipped_seg.from[0] = rect.min[0];
			clipped_seg.from[1] = ((y0-y1)*rect.min[0] + x0*y1 - x1*y0)/(x0 - x1);
			continue;
		}
		if(checkPosF & 2) {
			clipped_seg.from[0] = rect.max[0];
			clipped_seg.from[1] = ((y0-y1)*rect.max[0] + x0*y1 - x1*y0)/(x0 - x1);
			continue;
		}
		if(checkPosF & 4) {
			clipped_seg.from[1] = rect.min[1];
			clipped_seg.from[0] = ((x1-x0)*rect.min[1] + x0*y1 - x1*y0)/(y1-y0);
			continue;
		}
		if(checkPosF & 8) {
			clipped_seg.from[1] = rect.max[1];
			clipped_seg.from[0] = ((x1-x0)*rect.max[1] + x0*y1 - x1*y0)/(y1-y0);
			continue;
		}

		if(checkPosT & 1) {
			clipped_seg.to[0] = rect.min[0];
			clipped_seg.to[1] = ((y0-y1)*rect.min[0] + x0*y1 - x1*y0)/(x0 - x1);
			continue;
		}
		if(checkPosT & 2) {
			clipped_seg.to[0] = rect.max[0];
			clipped_seg.to[1] = ((y0-y1)*rect.max[0] + x0*y1 - x1*y0)/(x0 - x1);
			continue;
		}
		if(checkPosT & 4) {
			clipped_seg.to[1] = rect.min[1];
			clipped_seg.to[0] = ((x1-x0)*rect.min[1] + x0*y1 - x1*y0)/(y1-y0);
			continue;
		}
		if(checkPosT & 8) {
			clipped_seg.to[1] = rect.max[1];
			clipped_seg.to[0] = ((x1-x0)*rect.max[1] + x0*y1 - x1*y0)/(y1-y0);
			continue;
		}
	}
}
