/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the lottie-qt module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "bmpathtrimmer.h"

#include "bmtrimpath.h"
#include "renderer.h"

#include <QPainterPath>

namespace Lottie {

BMPathTrimmer::BMPathTrimmer(BMBase *root)
: m_root(root) {
	Q_ASSERT(m_root);
}

void BMPathTrimmer::addTrim(BMTrimPath* trim) {
	if (!trim) {
		return;
	}

	m_trimPaths.append(trim);

	if (!m_appliedTrim) {
		m_appliedTrim = trim;
	} else {
		qWarning()
			<< "BM Shape Layer: more than one trim path found on the layer."
			<< "Only one (the first encountered) is supported";
	}
}

bool BMPathTrimmer::inUse() const {
	return !m_trimPaths.isEmpty();
}

void BMPathTrimmer::applyTrim(BMShape *shape) {
	if (!m_appliedTrim) {
		return;
	}
	shape->applyTrim(*m_appliedTrim);
}

void BMPathTrimmer::updateProperties(int frame) {
	QPainterPath unifiedPath;

	if (m_appliedTrim) {
		m_appliedTrim->updateProperties(frame);
	}

//	for (BMBase *child : m_root->children()) {
//		// TODO: Create a better system for recognizing types
//		if (child->type() >= 1000) {
//			continue;
//		}

//		BMShape *shape = static_cast<BMShape*>(child);

//		// TODO: Get a better way to inherit trimming
//		if (shape->type() == BM_SHAPE_GROUP_IX && m_appliedTrim) {
//			shape->applyTrim(*m_appliedTrim);
//		}

//		shape->updateProperties(frame);

//		if (m_appliedTrim && shape->acceptsTrim()) {
//			shape->applyTrim(*m_appliedTrim);
//		}
//	}
}

void BMPathTrimmer::render(Renderer &renderer, int frame) const {
	Q_UNUSED(renderer);
//	if (m_appliedTrim) {
//		renderer.render(*m_appliedTrim);
//	}
}

} // namespace Lottie
