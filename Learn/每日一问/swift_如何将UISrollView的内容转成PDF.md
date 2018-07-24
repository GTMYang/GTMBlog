swift 如何将UISrollView的内容转成PDF?
===

[官方参考文档地址](https://developer.apple.com/documentation/uikit/1623931-uigraphicsbeginpdfcontexttodata?language=occ#see-also)

```swift

func PDFWithScrollView(scrollview: UIScrollView) -> NSData {

        let pageDimensions = scrollview.bounds

        let pageSize = pageDimensions.size
        let totalSize = scrollview.contentSize

        // 计算页的行数和列数
        let numberOfPagesThatFitHorizontally = Int(ceil(totalSize.width / pageSize.width))
        let numberOfPagesThatFitVertically = Int(ceil(totalSize.height / pageSize.height))


        let outputData = NSMutableData()
        // 创建一个PDF-based图形上下文，并将该context设置为当前绘制的上下文
        // 参数 outputData 数据输出到outputData
        // 参数 pageDimensions:CGRect （A rectangle that specifies the default size and location of PDF pages）
        UIGraphicsBeginPDFContextToData(outputData, pageDimensions, nil)

        // 记录scrollview原始状态，绘制完需要恢复原始状态
        let savedContentOffset = scrollview.contentOffset
        let savedContentInset = scrollview.contentInset
        // 去掉scrollview的边距
        scrollview.contentInset = UIEdgeInsets.zero
        if let context = UIGraphicsGetCurrentContext()
        {
            for indexHorizontal in 0 ..< numberOfPagesThatFitHorizontally
            {
                for indexVertical in 0 ..< numberOfPagesThatFitVertically
                {


                    // UIGraphicsBeginPDFContextToData时设置的页尺寸，结束前面的页
                    // 开始新的页
                    UIGraphicsBeginPDFPage()

                    // 计算当前页在scrollView中的offset
                    let offsetHorizontal = CGFloat(indexHorizontal) * pageSize.width
                    let offsetVertical = CGFloat(indexVertical) * pageSize.height
                    // scrollView滚动到对应的位置
                    scrollview.contentOffset = CGPoint(x: offsetHorizontal, y: offsetVertical)  

                    //CGContextTranslateCTM(context, -offsetHorizontal, -offsetVertical) // NOTE: Negative offsets
                    // context移位到新的绘制区域
                    context.translateBy(x: -offsetHorizontal, y: -offsetVertical) // NOTE: Negative offsets

                    // scrollview的图层在context中渲染
                    scrollview.layer.render(in: context)
                }
            }
        }

        // 关闭当前context，并从current context stack中pop
        UIGraphicsEndPDFContext()

        // 恢复 scrollview状态
        scrollview.contentInset = savedContentInset
        scrollview.contentOffset = savedContentOffset


        return outputData
    }

```
