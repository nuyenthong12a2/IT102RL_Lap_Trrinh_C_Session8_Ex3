1. Phân tích Input/Output (dùng cho README.md)

Input: N (1 đến 100), rồi với mỗi tài khoản: account_id, plan_type (0 đến 2), monthly_fee, remaining_days, active_devices. Ba trường cuối được phép là dữ liệu "bẩn" (âm, sai phí, quá lớn).

Output:

Bảng tài khoản sau kiểm toán và sắp xếp.
MRR trước kiểm toán, MRR sau kiểm toán, chênh lệch.
Số tài khoản bị hạ cấp và số tài khoản bị cắt giảm thiết bị.
2. Hai giải pháp

Giải pháp A (tại chỗ): kiểm toán từng phần tử trên mảng gốc, rồi sắp xếp chèn (insertion sort) theo monthly_fee giảm dần. Vì tài khoản trả phí luôn có phí lớn hơn 0 còn Free có phí 0, một lần sắp xếp theo phí giảm dần đã đẩy Free xuống cuối. Insertion sort là thuật toán ổn định nên thứ tự ban đầu của các tài khoản cùng phí được giữ nguyên.

Giải pháp B (mảng phụ): kiểm toán xong thì tách vào hai mảng struct phụ paid_list[] và free_list[], sắp xếp paid_list giảm dần theo phí, rồi ghép paid_list và free_list ngược lại mảng chính.

3. Bảng so sánh
Tiêu chí	Giải pháp A (in-place)	Giải pháp B (mảng phụ)
Time Complexity	O(N²) trường hợp xấu (insertion sort)	O(N²) cho nhóm trả phí, cộng O(N) tách và ghép
Space Complexity	O(1): chỉ thêm 1 biến struct tạm	O(N): thêm 2 mảng struct (tối đa 100 phần tử mỗi mảng)
Độ phức tạp mã (không có hàm)	Thấp: một khối kiểm toán và một khối sắp xếp	Cao hơn: thêm 2 mảng, 2 bộ đếm, 3 vòng lặp tách, sắp xếp, ghép
Rủi ro lỗi logic trong main()	Chủ yếu ở điều kiện dừng j >= 0 và dấu so sánh (< thay vì <= sẽ mất tính ổn định)	Dễ sai chỉ số khi ghép, dễ quên reset bộ đếm, nhiều biến hơn để theo dõi
4. Biện luận chọn Giải pháp A
Với N tối đa 100, chênh lệch tốc độ giữa hai giải pháp không đáng kể, nên bộ nhớ phụ và độ phức tạp mã trở thành yếu tố quyết định.
A không tốn bộ nhớ phụ, phù hợp môi trường hạn chế, và ít biến hơn nên ít rủi ro sai chỉ số trong ràng buộc "chỉ có main()".
A xử lý gọn Edge Case 4 (toàn bộ hết hạn hoặc toàn bộ hợp lệ): insertion sort không dịch chuyển gì khi mọi phí bằng nhau, và điều kiện j >= 0 chặn truy cập ngoài mảng. Với B, nhóm rỗng phải được xử lý riêng.
Bù lại, A có O(N²). Nếu N lên đến hàng chục nghìn thì nên chuyển sang B hoặc dùng sắp xếp hiệu quả hơn.
5. Mã giả (Giải pháp A)
NHAP N, lap den khi 1 <= N <= 100
NHAP tung tai khoan (plan_type lap den khi thuoc [0,2])

VOI MOI tai khoan i:
    mrr_truoc += phi_chuan(plan_type)
    NEU remaining_days <= 0:
        NEU plan_type > 0: plan_type = 0, dem_ha_cap++
        remaining_days = 0
    monthly_fee = phi_chuan(plan_type)
    NEU active_devices <= 0: active_devices = 1
    NEU con han VA active_devices > gioi_han(plan_type):
        active_devices = gioi_han(plan_type), dem_cat_giam++
    mrr_sau += monthly_fee

VOI i = 1 DEN N-1:                      // insertion sort on dinh
    key = accounts[i]; j = i - 1
    TRONG KHI j >= 0 VA accounts[j].fee < key.fee:
        accounts[j+1] = accounts[j]; j--
    accounts[j+1] = key

IN bang, MRR truoc, MRR sau, chenh lech