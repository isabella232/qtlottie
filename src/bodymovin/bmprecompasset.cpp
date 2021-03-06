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
#include "bmprecompasset.h"

#include "bmlayer.h"

namespace Lottie {

BMPreCompAsset::BMPreCompAsset(BMBase *parent) : BMAsset(parent) {
}

BMPreCompAsset::BMPreCompAsset(BMBase *parent, const BMPreCompAsset &other)
: BMAsset(parent, other) {
}

BMPreCompAsset *BMPreCompAsset::clone(BMBase *parent) const {
	return new BMPreCompAsset(parent, *this);
}

BMPreCompAsset::BMPreCompAsset(BMBase *parent, const JsonObject &definition)
: BMAsset(parent) {
	BMAsset::parse(definition);
	if (m_hidden) {
		return;
	}

	const auto layers = definition.value("layers").toArray();
	for (auto i = layers.end(); i != layers.begin();) {
		const auto &entry = *(--i);
		if (const auto layer = BMLayer::construct(this, entry.toObject())) {
			// Mask layers must be rendered before the layers they affect to
			// although they appear before in layer hierarchy. For this reason
			// move a mask after the affected layers, so it will be rendered first
			if (layer->isMaskLayer()) {
				prependChild(layer);
			} else {
				appendChild(layer);
			}
		}
	}
}

} // namespace Lottie
